/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:04:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/09 16:03:42 by jose-ara         ###   ########.fr       */
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
		if (fd == -1)
		{
			perror(cinfo->input_file);
			return (1);
		}
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
		{
			perror(cinfo->output_file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

void	child_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_cinfo	*cinfo;
	char	*cmd_path;
	char	**cmd_and_args;
	char	**envp_exec;

	cinfo = shell_data->einfo->cinfos[index];
	rl_clear_history();
	if (redirect_input(cinfo, pipe_aux) || redirect_output(shell_data, cinfo,
			pipes, index))
		return (perror("File not found"), free_shell_data(shell_data),
			exit(EXIT_FAILURE));
	free_splitted_string(shell_data->shell_envi.envp_exec);
	generate_exec_envp(&(shell_data->shell_envi));
	restore_terminal_signals();
	cmd_path = cinfo->cmd_and_args[0];
	cmd_and_args = cinfo->cmd_and_args;
	envp_exec = shell_data->shell_envi.envp_exec;
	if (cmd_path && cmd_path[0])
		execve(cmd_path, cmd_and_args, envp_exec);
	perror("Command not found");
	free_shell_data(shell_data);
	exit(127);
}

void	exec_subshell(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_cinfo	*cinfo;
	int		exit_status;

	cinfo = shell_data->einfo->cinfos[index];
	rl_clear_history();
	if (redirect_input(cinfo, pipe_aux) || redirect_output(shell_data, cinfo,
			pipes, index))
		return (perror("File not found"), free_shell_data(shell_data),
			exit(EXIT_FAILURE));
	restore_terminal_signals();
	exit_status = exec_built_in(shell_data, cinfo);
	free_shell_data(shell_data);
	exit(exit_status);
}
