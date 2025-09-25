/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:04:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/08/01 13:17:45 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern sig_atomic_t signal_recv;

static void redirect_input(t_shell_data *shell_data, int *pipe_aux, int index)
{
	int fd;

	if (index == 0 && shell_data->einfo->input_file)
	{
		fd = open(shell_data->einfo->input_file, O_RDONLY);
		if (fd == -1)
			return (perror ("Error\n"), (void) 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (shell_data->einfo->n_pipes)
	{
		dup2(*pipe_aux, STDIN_FILENO);
		close(*pipe_aux);
		*pipe_aux = -1;
	}

}

static void redirect_output(t_shell_data *shell_data, int pipes[2],int index)
{
	int fd;

	if ((index == shell_data->einfo->n_pipes) && shell_data->einfo->output_file)
	{
		fd = open(shell_data->einfo->output_file, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (perror ("Error\n"), (void) 0);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (shell_data->einfo->n_pipes && (shell_data->einfo->n_pipes!= index))
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
	}

}

void	child_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux ,int index)
{
	redirect_input(shell_data, pipe_aux, index);
	redirect_output(shell_data,pipes,index);
	free_splitted_string(shell_data->shell_envi.envp_exec);
	generate_exec_envp(&(shell_data->shell_envi));
	restore_terminal_signals();
	if (shell_data->einfo->commands[index] && shell_data->einfo->commands[index][0] != NULL)
		execve(shell_data->einfo->commands[index][0], shell_data->einfo->commands[index], shell_data->shell_envi.envp_exec);
	//liberar todo de einfo
	rl_clear_history();
	free_tokens(shell_data->tokens);
	free_shell_data(shell_data);
	exit(EXIT_FAILURE);
}

void redirect_input_subshell(t_shell_data *shell_data, int *pipe_aux)
{
	t_piped_info *piped_info;
	int fd;

	piped_info = get_last_pipe_info_entry(shell_data);
	if (!piped_info)
		exit(EXIT_FAILURE);
	fd = open (piped_info->file_cmmd_name, O_RDWR, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (*pipe_aux != -1)
		close(*pipe_aux);
	*pipe_aux = -1;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void exec_subshell(t_shell_data *shell_data, int pipes[2], int *pipe_aux, int index)
{
	char *args[2];

	args[0] = "minishell";
	args[1] = NULL;
	redirect_input_subshell(shell_data, pipe_aux);
	redirect_output(shell_data, pipes, index);
	free_splitted_string(shell_data->shell_envi.envp_exec);
	generate_exec_envp(&(shell_data->shell_envi));
	restore_terminal_signals();
	execve(args[0], args, shell_data->shell_envi.envp_exec);
	//liberar todo de einfo
	rl_clear_history();
	free_tokens(shell_data->tokens);
	free_shell_data(shell_data);
	exit(EXIT_FAILURE);
}
