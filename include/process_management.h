/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:35:46 by pablo             #+#    #+#             */
/*   Updated: 2025/11/10 20:51:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_MANAGEMENT_H
# define PROCESS_MANAGEMENT_H
# include "structs.h"

/**
 * @brief Handles the execution of a child process in the minishell.
 *
 * This function is responsible for setting up the child process
 * environment, including input/output redirections, signal restoration,
 * and command execution. It clears the readline history, performs
 * redirections, generates the execution environment, and attempts to
 * execute the command using execve. If any step fails, it handles errors
 * appropriately and exits the process.
 *
 * @param shell_data Pointer to the shell data structure containing
 *                   environment and command information.
 * @param pipes      Array of two integers representing the pipe file
 *                   descriptors for inter-process communication.
 * @param pipe_aux   Pointer to an auxiliary pipe array, used for input
 *                   redirection in pipelines.
 * @param index      Index of the command info structure in the shell data
 *                   to process.
 *
 * @note This function does not return ; it either executes the command or
 *       exits the process with an appropriate status code (EXIT_FAILURE
 *       or 127).
 */
void	child_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
			int index);

/**
 * @brief Executes the command cycle for the shell, handling piping and
 * process forking.
 *
 * This function iterates through each command in the execution info,
 * managing pipes and forking processes as needed. For non-built-in
 * commands, it forks a child process to execute the command, while the
 * parent handles pipe management and waits for completion. Built-in
 * commands are handled directly without forking.
 *
 * @param shell_data Pointer to the shell data structure containing
 * execution info, process IDs, and other relevant shell state.
 *
 * @note This function assumes that the shell_data structure is properly
 * initialized and that the execution info (einfo) contains valid command
 * information. It handles pipe creation, redirection, and process
 * synchronization.
 */
void	execution_cycle(t_shell_data *shell_data);

/**
 * @brief Executes a subshell process for the given command info.
 *
 * This function handles the execution of a subshell by performing input
 * and output redirections, restoring terminal signals, executing built-in
 * commands, and properly exiting the process. If redirection fails, it
 * prints an error and exits with failure.
 *
 * @param shell_data Pointer to the shell data structure containing
 * execution information.
 * @param pipes Array of two integers representing the pipe file
 * descriptors for output redirection.
 * @param pipe_aux Pointer to an auxiliary pipe array for input
 * redirection.
 * @param index Index of the command info in the execution info's cinfos
 * array.
 */
void	exec_subshell(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
			int index);

/**
 * @brief Handles the parent process logic after forking child
 * processes in a shell.
 *
 * This function manages the parent process responsibilities,
 * including closing file descriptors, waiting for child processes
 * to complete, and updating the shell's exit status based on the
 * last command's exit code. It differentiates between piped and
 * non-piped command executions.
 *
 * @param shell_data Pointer to the shell data structure containing
 * execution information.
 * @param pipes Array of pipe file descriptors for inter-process
 * communication.
 * @param pipe_aux Auxiliary pipe array, possibly for additional
 * piping needs.
 * @param index The current command index in the pipeline (0-based).
 *
 * @note If there are pipes and the index does not match the total
 * number of pipes, the function returns early without waiting. For
 * piped commands, it waits for all processes in the pipeline. For
 * non-piped commands, it waits for the single forked process. The
 * exit status is modified only when processing the last command in
 * the pipeline.
 */
void	parent_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
			int index);

#endif
