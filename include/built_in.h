/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:34:00 by pablo             #+#    #+#             */
/*   Updated: 2025/11/10 20:51:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "structs.h"
# include "libft.h"

/**
 * @brief Implements the cd (change directory) built-in command for the shell.
 *
 * This function handles changing the current working directory based on the
 * provided arguments. It supports changing to a specified directory, or to
 * the HOME directory if no argument is given. It also updates the PWD and
 * OLDPWD environment variables accordingly.
 *
 * @param shell_data Pointer to the shell data structure containing
 * environment variables and other shell state.
 * @param cinfo Pointer to the command info structure containing the command
 * and its arguments.
 * @param ret Pointer to an integer where the return status is stored (1 for
 * success, -1 for error).
 *
 * @return void (return status is set via the ret parameter).
 *
 * Error handling:
 * - If more than one argument is provided, sets errno to EINVAL and prints
 * an error.
 * - If HOME is not set and no argument is provided, sets errno to ENOENT
 * and prints an error.
 * - If chdir fails, prints an error message.
 */
void	cd_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);

/**
 * @brief Checks if the command name matches any built-in shell command.
 *
 * This function examines the first argument in the cmd_and_args array of the
 * provided t_cinfo structure. It compares it against a predefined list of
 * built-in commands ("exit", "pwd", "cd", "echo", "env", "export", "unset")
 * using ft_strncmp, limited to the maximum length of the two strings being
 * compared.
 *
 * @param cinfo A pointer to the t_cinfo structure containing command and
 *              argument information.
 * @return 1 if the command name matches a built-in command, 0 otherwise.
 */
int		check_built_in_name(t_cinfo *cinfo);

/**
 * @brief Checks if the command is a built-in and executes it if
 * applicable.
 *
 * This function determines whether the given command is a built-in
 * command. If it is, it handles input and output redirections,
 * executes the built-in, restores the original file descriptors,
 * and updates the exit status accordingly. If the command is not a
 * built-in or if there are pipes, it returns 0 without execution.
 *
 * @param shell_data Pointer to the shell data structure containing
 * environment and execution info.
 * @param cinfo Pointer to the command info structure containing
 * command details.
 * @return 1 if the command was a built-in and execution was
 * attempted (success or failure), 0 if the command is not a
 * built-in or if there are pipes.
 *
 * @note This function modifies the exit status in the shell
 * environment based on execution results. Redirections are
 * temporarily applied and restored after execution.
 */
int		check_if_is_built_in(t_shell_data *shell_data, t_cinfo *cinfo);

/**
 * @brief Implements the echo command for the minishell.
 *
 * This function processes the echo command arguments. It checks for the "-n"
 * option to suppress the trailing newline. It then prints all subsequent
 * arguments to standard output, separated by spaces, and appends a newline
 * unless "-n" is specified.
 *
 * @param cinfo Pointer to the command information structure containing command
 * and arguments.
 * @param ret Pointer to an integer where the return status is stored (set to
 * 1).
 */
void	echo_cmd(t_cinfo *cinfo, int *ret);

/**
 * @brief Executes the 'env' built-in command.
 *
 * This function handles the 'env' command in the minishell. It checks if
 * there are any arguments provided (beyond the command itself). If
 * arguments are present, it sets the return value to -1, sets errno to
 * EINVAL, prints an error message, and returns. Otherwise, it prints the
 * current environment variables.
 *
 * @param cinfo Pointer to the command information structure, containing
 *              details about the command and its arguments.
 * @param enviroment Pointer to the environment structure, holding the
 *                   list of environment variables.
 * @param ret Pointer to an integer where the return status is stored.
 *            Set to 1 on success, -1 on error.
 */
void	env_cmd(t_cinfo *cinfo, t_envp *enviroment, int *ret);

/**
 * Executes a built-in shell command based on the command name in the
 * command info structure. This function checks the first argument of
 * the command (cinfo->cmd_and_args[0]) against known built-in commands
 * and calls the appropriate handler function. It handles commands like
 * exit, pwd, cd, echo, env, export, and unset.
 *
 * @param shell_data A pointer to the shell data structure containing
 *                   shell state and environment.
 * @param cinfo A pointer to the command info structure containing the
 *              command and its arguments.
 * @return The return value from the executed built-in command, or 0 if
 *         no valid command is found or if cinfo is invalid.
 */
int		exec_built_in(t_shell_data *shell_data, t_cinfo *cinfo);

/**
 * @brief Handles the export command in the shell.
 *
 * This function processes the export command arguments. If no arguments
 * are provided, it prints the ordered environment list. For each argument,
 * it parses the key-value pair and updates the shell's environment lists
 * accordingly.
 *
 * @param shell_data Pointer to the shell data structure containing
 * environment information.
 * @param cinfo Pointer to the command information structure with command
 * arguments.
 * @param ret Pointer to an integer where the return status is stored (set
 * to 1 initially).
 */
void	export_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);

/**
 * @brief Handles the exit command for the minishell.
 *
 * This function processes the exit command, validating arguments and
 * determining the exit status. It supports exiting with a specified
 * numeric status or using a default value from an environment variable
 * if no argument is provided.
 *
 * @param shell_data Pointer to the shell data structure containing
 *                   environment and other shell-related information.
 * @param cinfo      Pointer to the command information structure,
 *                   including the command arguments array and its size.
 * @param ret        Pointer to an integer where the return status is set
 *                   in case of errors (e.g., invalid arguments).
 *
 * Behavior:
 * - If more than one argument is provided (array_size > 2), sets errno
 *   to E2BIG and returns with *ret = -1.
 *
 * - If the argument is not a valid number, sets errno to EINVAL and
 *   returns with *ret = -1.
 *
 * - If no arguments are provided (array_size == 1), retrieves the value
 *   of the "FT_EXIT_ENV" environment variable. If it exists, uses its
 *   integer value; otherwise, defaults to 0.
 *
 * - If one argument is provided, converts it to an integer using
 *   ft_atoi.
 *
 * - Clears the readline history, frees shell data, and exits the
 *   program with the computed status modulo 256.
 *
 * @note This function does not return (on successful execution); it
 *       terminates the program via exit().
 */
void	exit_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);

/**
 * @brief Prints the environment list in different formats based on the mode.
 *
 * This function iterates through a linked list of environment variables and
 * prints them either in a simple key=value format (if mode is non-zero) or
 * in a bash-style declare -x format (if mode is zero). If mode is non-zero,
 * it also prints a RESET string at the end.
 *
 * @param envp_list A pointer to the head of the linked list of environment
 *                  variables. Each node contains a key and optionally a value.
 * @param mode      An integer flag that determines the output format:
 *                  - If non-zero, prints in "key=value" format.
 *                  - If zero, prints in "declare -x key" format, using
 *                    print_literal for the value if present.
 *
 * @note If envp_list is NULL, the function returns immediately without
 *       printing anything.
 * @note Assumes that print_literal is defined elsewhere and handles proper
 *       escaping for bash declare statements.
 * @note RESET is assumed to be a defined constant (e.g., ANSI escape code
 *       for reset).
 */
void	print_envi_list(t_linked_env *envp_list, int mode);

/**
 * @brief Implements the pwd builtin command for the minishell.
 * Retrieves and prints the current working directory to stdout.
 * Sets the return status via the provided pointer.
 *
 * @param ret Pointer to an integer to store the command's exit status.
 *            Set to 1 on successful execution, -1 if getcwd fails.
 */
void	pwd_cmd(int *ret);

/**
 * @brief Unsets environment variables specified in the command arguments.
 *
 * This function processes the arguments of the unset command, starting
 * from the second argument (index 1 in cmd_and_args). For each argument,
 * it checks if the variable exists in both the environment list (envp)
 * and the ordered environment list (ordered_envp). If it does, it
 * decrements the length of the environment list (len_env). The actual
 * removal of the variables from the lists is not performed here; this
 * function only updates the length counter.
 *
 * @param shell_data Pointer to the shell data structure containing
 * environment information.
 * @param cinfo Pointer to the command information structure containing
 * the command and its arguments.
 * @param ret Pointer to an integer where the return status is stored
 * (set to 1 initially).
 */
void	unset_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);

#endif
