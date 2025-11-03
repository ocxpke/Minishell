/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:04:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/10/28 18:14:03 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_signal_recv;

//TODO: Hacer un exit on file error

static void	redirect_input(t_cinfo *cinfo, int *pipe_aux)
{
	int	fd;

	if ((*pipe_aux) != -1)
	{
		dup2(*pipe_aux, STDIN_FILENO);
		close(*pipe_aux);
		*pipe_aux = -1;
	}
	if (cinfo->input_file)
	{
		fd = open(cinfo->input_file, O_RDONLY, 0644);
		if (fd == -1)
			exit(EXIT_FAILURE);//TODO: Exitear comando bien
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	redirect_output(t_shell_data *shell_data, t_cinfo *cinfo, int pipes[2], int index)
{
	int	fd;

	if (index != shell_data->einfo->n_pipes)
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
	}
	if (cinfo->output_file)
	{
		printf("El comando es %s\n", cinfo->cmd_and_args[0]);
		if (cinfo->is_append)
			fd = open(cinfo->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cinfo->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(EXIT_FAILURE);//TODO: Exitear comando bien
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	child_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_cinfo *cinfo;

	cinfo = shell_data->einfo->cinfos[index];
	redirect_input(cinfo, pipe_aux);
	redirect_output(shell_data, cinfo, pipes, index);
	free_splitted_string(shell_data->shell_envi.envp_exec);
	generate_exec_envp(&(shell_data->shell_envi));
	restore_terminal_signals();
	if (shell_data->einfo->cinfos[index]->cmd_and_args[0]
		&& shell_data->einfo->cinfos[index]->cmd_and_args[0][0])
		execve(shell_data->einfo->cinfos[index]->cmd_and_args[0],
			shell_data->einfo->cinfos[index]->cmd_and_args,
			shell_data->shell_envi.envp_exec);
	//TODO: liberar todo de einfo
	rl_clear_history();
	free_shell_data(shell_data);
	exit(EXIT_FAILURE);
}

void	exec_subshell(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_cinfo *cinfo;

	cinfo = shell_data->einfo->cinfos[index];
	redirect_input(cinfo, pipe_aux);
	redirect_output(shell_data, cinfo, pipes, index);
	restore_terminal_signals();
	exec_built_in(shell_data, cinfo);
	// if (shell_data->einfo->n_pipes == index)
	// 	close(STDIN_FILENO);
	// else
	// 	close(STDOUT_FILENO);
	rl_clear_history();
	free_shell_data(shell_data);
	exit(EXIT_SUCCESS);
}
