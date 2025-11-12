#!/usr/bin/env bash
set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
MINISHELL_BIN="${MINISHELL_BIN:-${REPO_ROOT}/build/minishell}"
BASH_BIN="${BASH_BIN:-/bin/bash}"
VALGRIND_SUPP="${REPO_ROOT}/build/readline.supp"

# Check if --valgrind flag is passed
USE_VALGRIND=0
if [ "${1:-}" = "--valgrind" ]; then
	USE_VALGRIND=1
	if ! command -v valgrind &> /dev/null; then
		printf 'valgrind not found. Please install it.\n' >&2
		exit 1
	fi
	if [ ! -f "${VALGRIND_SUPP}" ]; then
		printf 'Valgrind suppression file not found at %s.\n' "${VALGRIND_SUPP}" >&2
		exit 1
	fi
fi

if [ ! -x "${MINISHELL_BIN}" ]; then
	printf 'Minishell binary not found at %s. Build it first (e.g. make).\n' "${MINISHELL_BIN}" >&2
	exit 1
fi

if [ ! -x "${BASH_BIN}" ]; then
	printf 'Bash binary not found at %s.\n' "${BASH_BIN}" >&2
	exit 1
fi

TMP_DIR="$(mktemp -d)"
trap 'rm -rf "${TMP_DIR}"' EXIT

declare -a TEST_NAMES=()
declare -a TEST_CMDS=()
declare -a TEST_TYPES=()
declare -a TEST_EXPECTED_OUTPUTS=()
declare -a TEST_EXPECTED_STATUS=()

add_bash_test() {
	TEST_NAMES+=("$1")
	TEST_CMDS+=("$2")
	TEST_TYPES+=("bash")
	TEST_EXPECTED_OUTPUTS+=("")
	TEST_EXPECTED_STATUS+=("")
}

add_literal_test() {
	TEST_NAMES+=("$1")
	TEST_CMDS+=("$2")
	TEST_TYPES+=("literal")
	TEST_EXPECTED_OUTPUTS+=("$3")
	TEST_EXPECTED_STATUS+=("${4:-0}")
}

add_bash_test "empty_line" ""
add_bash_test "spaces_only" "   "
add_bash_test "simple_echo" "echo hola"
add_bash_test "echo_args" "echo hola mundo"
add_bash_test "single_quotes" $'echo \'hola mundo\''
add_bash_test "double_quotes" $'echo "hola mundo"'
add_bash_test "variable_expansion" 'echo hola $USER'
add_bash_test "double_quotes_expansion" 'echo "Hola $USER"'
add_bash_test "export_and_print" $'export MINI_VAR=42\necho $MINI_VAR'
add_bash_test "export_unset" $'export MINI_VAR=42\nunset MINI_VAR\necho $MINI_VAR'
add_bash_test "exit_builtin" "exit"
add_bash_test "exit_status" "exit 42"
add_bash_test "pwd_builtin" "pwd"
add_bash_test "cd_and_pwd" $'pwd\ncd ..\npwd'
add_literal_test "cd_error" "cd /path/that/does/not/exist" "bash: cd: /path/that/does/not/exist: No such file or directory" 1
add_bash_test "external_bin" "ls --color=never"
add_bash_test "pipe_basic" "echo hola | cat -e"
add_bash_test "pipeline_three" 'printf "uno\ndos\n" | grep dos | wc -l'
add_bash_test "false_status" $'false\necho $?'
add_bash_test "true_status" $'true\necho $?'
add_bash_test "redirection_overwrite" $'echo hola > __TMP__/redir.txt\ncat __TMP__/redir.txt'
add_bash_test "redirection_append" $'echo uno > __TMP__/append.txt\necho dos >> __TMP__/append.txt\ncat __TMP__/append.txt'
add_bash_test "mixed_quotes" $'echo "comillas \'mixtas\'"'
add_bash_test "redirect_stdin" $'echo abc > __TMP__/stdin.txt\ncat < __TMP__/stdin.txt'
add_bash_test "pipe_with_builtin" $'export MINI_VAR=test\necho $MINI_VAR | cat'

# Built-in error code tests
add_bash_test "echo_exit_code" $'echo hola\necho $?'
add_bash_test "pwd_exit_code" $'pwd\necho $?'
add_bash_test "env_exit_code" $'env | grep USER\necho $?'
add_bash_test "export_valid_exit_code" $'export TEST_VAR=value\necho $?'
add_literal_test "export_invalid_exit_code" $'export 123INVALID=value\necho $?' $'bash: export: `123INVALID=value\': not a valid identifier\n1' 0
add_bash_test "unset_exit_code" $'export TEST_VAR=value\nunset TEST_VAR\necho $?'
add_bash_test "unset_invalid_exit_code" $'unset 123INVALID\necho $?'
add_bash_test "cd_success_exit_code" $'cd .\necho $?'
add_bash_test "cd_home_exit_code" $'cd\necho $?'
add_literal_test "cd_too_many_args" $'cd arg1 arg2\necho $?' $'bash: cd: too many arguments\n1' 0

PASS_COUNT=0
FAIL_COUNT=0
LEAK_COUNT=0

print_command() {
	local cmd="$1"
	printf '%q' "${cmd}"
}

run_minishell() {
	local cmd="$1"
	if [ "${USE_VALGRIND}" -eq 1 ]; then
		valgrind --leak-check=full --show-leak-kinds=definite,indirect,possible \
			--suppressions="${VALGRIND_SUPP}" --log-file="${TMP_DIR}/valgrind.log" \
			"${MINISHELL_BIN}" 2>&1
	else
		"${MINISHELL_BIN}" 2>&1
	fi
}

check_for_leaks() {
	if [ "${USE_VALGRIND}" -eq 1 ] && [ -f "${TMP_DIR}/valgrind.log" ]; then
		# Check for definitely lost, indirectly lost, or possibly lost bytes
		# Take only the first match (in case of multiple processes in pipes)
		local def_lost=$(grep "definitely lost:" "${TMP_DIR}/valgrind.log" | head -1 | awk '{print $4}')
		local ind_lost=$(grep "indirectly lost:" "${TMP_DIR}/valgrind.log" | head -1 | awk '{print $4}')
		local pos_lost=$(grep "possibly lost:" "${TMP_DIR}/valgrind.log" | head -1 | awk '{print $4}')

		# Convert to numbers (remove commas if any)
		def_lost=${def_lost//,/}
		ind_lost=${ind_lost//,/}
		pos_lost=${pos_lost//,/}

		# If any of them are greater than 0, we have a leak
		if [ "${def_lost:-0}" -gt 0 ] || [ "${ind_lost:-0}" -gt 0 ] || [ "${pos_lost:-0}" -gt 0 ]; then
			return 1  # Has leaks
		fi
	fi
	return 0  # No leaks
}

for idx in "${!TEST_NAMES[@]}"; do
	test_name="${TEST_NAMES[$idx]}"
	cmd="${TEST_CMDS[$idx]}"
	cmd="${cmd//__TMP__/${TMP_DIR}}"
	display="$(print_command "${cmd}")"
	printf '\n==> (%02d/%02d) %s :: %s\n' "$((idx + 1))" "${#TEST_NAMES[@]}" "${test_name}" "${display}"

	test_type="${TEST_TYPES[$idx]}"

	case "${test_type}" in
	"bash")
		bash_output=$(printf '%s\nexit\n' "${cmd}" | "${BASH_BIN}" --norc --noprofile 2>&1)
		bash_status=$?

		mini_output=$(printf '%s\nexit\n' "${cmd}" | run_minishell "${cmd}")
		mini_status=$?

		# Check for memory leaks
		has_leak=0
		if ! check_for_leaks; then
			has_leak=1
			LEAK_COUNT=$((LEAK_COUNT + 1))
		fi

		if [ "${bash_output}" = "${mini_output}" ] && [ "${bash_status}" -eq "${mini_status}" ] && [ "${has_leak}" -eq 0 ]; then
			printf '   PASS\n'
			PASS_COUNT=$((PASS_COUNT + 1))
			continue
		fi

		printf '   FAIL\n'
		FAIL_COUNT=$((FAIL_COUNT + 1))

		if [ "${has_leak}" -eq 1 ]; then
			printf '      MEMORY LEAK DETECTED\n'
			if [ -f "${TMP_DIR}/valgrind.log" ]; then
				printf '      Valgrind output:\n'
				cat "${TMP_DIR}/valgrind.log" | grep -A 5 "LEAK SUMMARY\|ERROR SUMMARY" | sed 's/^/         /'
			fi
		fi

		if [ "${bash_status}" -ne "${mini_status}" ]; then
			printf '      status bash=%d minishell=%d\n' "${bash_status}" "${mini_status}"
		fi

		if [ "${bash_output}" != "${mini_output}" ]; then
			printf '      output diff:\n'
			printf '%s' "${bash_output}" > "${TMP_DIR}/bash.out"
			printf '%s' "${mini_output}" > "${TMP_DIR}/mini.out"
			diff -u "${TMP_DIR}/bash.out" "${TMP_DIR}/mini.out" | sed 's/^/         /'
		fi
		;;
	"literal")
		expected_output="${TEST_EXPECTED_OUTPUTS[$idx]}"
		expected_status="${TEST_EXPECTED_STATUS[$idx]}"

		mini_output=$(printf '%s\necho EXITCODE:$?\nexit\n' "${cmd}" | run_minishell "${cmd}")
		mini_exit_code=$?
		mini_status=$(echo "${mini_output}" | grep -o 'EXITCODE:[0-9]*' | cut -d: -f2)
		mini_output=$(echo "${mini_output}" | grep -v 'EXITCODE:')

		# Check for memory leaks
		has_leak=0
		if ! check_for_leaks; then
			has_leak=1
			LEAK_COUNT=$((LEAK_COUNT + 1))
		fi

		if [ "${mini_output}" = "${expected_output}" ] && [ "${mini_status}" -eq "${expected_status}" ] && [ "${has_leak}" -eq 0 ]; then
			printf '   PASS\n'
			PASS_COUNT=$((PASS_COUNT + 1))
			continue
		fi

		printf '   FAIL\n'
		FAIL_COUNT=$((FAIL_COUNT + 1))

		if [ "${has_leak}" -eq 1 ]; then
			printf '      MEMORY LEAK DETECTED\n'
			if [ -f "${TMP_DIR}/valgrind.log" ]; then
				printf '      Valgrind output:\n'
				cat "${TMP_DIR}/valgrind.log" | grep -A 5 "LEAK SUMMARY\|ERROR SUMMARY" | sed 's/^/         /'
			fi
		fi

		if [ "${mini_status}" -ne "${expected_status}" ]; then
			printf '      status expected=%d minishell=%d\n' "${expected_status}" "${mini_status}"
		fi

		if [ "${mini_output}" != "${expected_output}" ]; then
			printf '      output diff:\n'
			printf '%s' "${expected_output}" > "${TMP_DIR}/expected.out"
			printf '%s' "${mini_output}" > "${TMP_DIR}/mini.out"
			diff -u "${TMP_DIR}/expected.out" "${TMP_DIR}/mini.out" | sed 's/^/         /'
		fi
		;;
	*)
		printf '   FAIL (unknown test type %s)\n' "${test_type}"
		FAIL_COUNT=$((FAIL_COUNT + 1))
		;;
	esac
	done

if [ "${USE_VALGRIND}" -eq 1 ]; then
	printf '\nSummary: %d passed, %d failed, %d leaks (%d total)\n' "${PASS_COUNT}" "${FAIL_COUNT}" "${LEAK_COUNT}" "${#TEST_NAMES[@]}"
else
	printf '\nSummary: %d passed, %d failed (%d total)\n' "${PASS_COUNT}" "${FAIL_COUNT}" "${#TEST_NAMES[@]}"
fi

if [ "${FAIL_COUNT}" -ne 0 ] || [ "${LEAK_COUNT}" -ne 0 ]; then
	exit 1
fi
