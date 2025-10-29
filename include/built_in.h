#include "minishell.h"

#ifndef BUILT_IN_H
#define BUILT_IN_H

void exit_cmd(t_shell_data *shell_data);
void cd_cmd(t_shell_data *shell_data, int *ret);
void pwd_cmd(int *ret);
void echo_cmd(t_shell_data *shell_data, int *ret);
void env_cmd(t_envp *enviroment, int *ret);
int check_if_is_built_in(t_shell_data *shell_data, int index);

/**
 * @brief Prints the environment variables from a linked list in
 * different formats based on the mode.
 *
 * This function iterates through a linked list of environment
 * variables and prints them. If mode is non-zero, it prints in a
 * simple "key=value" format (or just "key" if no value), followed
 * by a reset sequence at the end. If mode is zero, it prints in a
 * bash-like "declare -x key=\"value\"" format, using print_literal
 * to handle special characters in the value.
 *
 * @param envp_list A pointer to the head of the linked list of
 * environment variables (t_linked_env). If NULL, the function
 * returns immediately without printing anything.
 * @param mode An integer flag determining the output format:
 *
 * - Non-zero: Simple export format (key=value or key).
 *
 * - Zero: Bash declare -x format with quoted values.
 */
void print_envi_list(t_linked_env *envp_list, int mode);
void export_cmd(t_shell_data *shell_data, int *ret);
void unset_cmd(t_shell_data *shell_data, int *ret);
int check_built_in_name(t_shell_data *shell_data);
int	check_all_built_in(t_shell_data *shell_data, int index);

#endif
