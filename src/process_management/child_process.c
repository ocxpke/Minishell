/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:04:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/20 19:53:09 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_signal_recv;

static int	redirect_input(t_cinfo *cinfo, int *pipe_aux)
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
		if (!ft_strncmp(cinfo->input_file, "", 1) && cinfo->is_heredoc)
			return (write(STDERR_FILENO, "heredoc sigint\n", 12), 1);
		if (fd == -1)
			return (perror(cinfo->input_file), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

static int	redirect_output(t_shell_data *shell_data, t_cinfo *cinfo,
		int pipes[2], int index)
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
		if (cinfo->is_append)
			fd = open(cinfo->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cinfo->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(cinfo->output_file), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

void	child_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_cinfo	*cinfo;
	int		err_in;
	int		err_out;

	cinfo = shell_data->einfo->cinfos[index];
	rl_clear_history();
	err_in = redirect_input(cinfo, pipe_aux);
	err_out = redirect_output(shell_data, cinfo, pipes, index);
	if (err_in || err_out)
		return (free_shell_data(shell_data), exit(EXIT_FAILURE));
	ft_matrix_free((void ***)&shell_data->shell_envi.envp_exec, 0);
	generate_exec_envp(&(shell_data->shell_envi));
	restore_terminal_signals();
	if (cinfo->cmd_and_args[0])
		execve(cinfo->cmd_and_args[0], cinfo->cmd_and_args,
			shell_data->shell_envi.envp_exec);
	perror("Command not found");
	free_shell_data(shell_data);
	exit(127);
}

void	exec_subshell(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_cinfo	*cinfo;
	int		exit_status;
	int		err_in;
	int		err_out;

	cinfo = shell_data->einfo->cinfos[index];
	rl_clear_history();
	err_in = redirect_input(cinfo, pipe_aux);
	err_out = redirect_output(shell_data, cinfo, pipes, index);
	if (err_in || err_out)
		return (free_shell_data(shell_data), exit(EXIT_FAILURE));
	restore_terminal_signals();
	exit_status = exec_built_in(shell_data, cinfo);
	free_shell_data(shell_data);
	exit(exit_status);
}
