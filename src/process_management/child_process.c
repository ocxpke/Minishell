/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:04:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/10/27 17:25:37 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern sig_atomic_t	signal_recv;

static void	redirect_input(t_shell_data *shell_data, int *pipe_aux, int index)
{
	int	fd;

	// if (index == 0 && shell_data->einfo->input_file)
	if (index == 0 && shell_data->einfo->cinfos[index]->input_file)
	{
		// fd = open(shell_data->einfo->input_file, O_RDONLY);
		fd = open(shell_data->einfo->cinfos[index]->input_file, O_RDONLY);
		if (fd == -1)
			return (perror("Error\n"), (void)0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (shell_data->einfo->n_pipes)
	{
		if ((*pipe_aux) == -1)
			return;
		dup2(*pipe_aux, STDIN_FILENO);
		close(*pipe_aux);
		*pipe_aux = -1;
	}
}

static void	redirect_output(t_shell_data *shell_data, int pipes[2], int index)
{
	int	fd;

	// if ((index == shell_data->einfo->n_pipes)&& shell_data->einfo->output_file)
	if ((index == shell_data->einfo->n_pipes)
		&& shell_data->einfo->cinfos[index]->output_file)
		{
			// fd = open(shell_data->einfo->output_file, O_WRONLY | O_CREAT, 0644);
					fd = open(shell_data->einfo->cinfos[index]->output_file,
							O_WRONLY | O_CREAT, 0644);
					if (fd == -1)
						return (perror("Error\n"), (void)0);
					dup2(fd, STDOUT_FILENO);
					close(fd);
		}
		else if (shell_data->einfo->n_pipes
			&& (shell_data->einfo->n_pipes != index))
		{
			close(pipes[0]);
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[1]);
		}
}

void	child_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	redirect_input(shell_data, pipe_aux, index);
	redirect_output(shell_data, pipes, index);
	free_splitted_string(shell_data->shell_envi.envp_exec);
	generate_exec_envp(&(shell_data->shell_envi));
	restore_terminal_signals();
	if (shell_data->einfo->cinfos[index]->cmd_and_args[0]
		&& shell_data->einfo->cinfos[index]->cmd_and_args[0][0])
		execve(shell_data->einfo->cinfos[index]->cmd_and_args[0],
			shell_data->einfo->cinfos[index]->cmd_and_args,
			shell_data->shell_envi.envp_exec);
	// liberar todo de einfo
	rl_clear_history();
	free_tokens(shell_data->tokens);
	free_shell_data(shell_data);
	exit(EXIT_FAILURE);
}

void	exec_subshell(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	redirect_input(shell_data, pipe_aux, index);
	redirect_output(shell_data, pipes, index);
	restore_terminal_signals();
	//ejecutar el comando de normal
	check_all_built_in(shell_data, index);
	// liberar todo de einfo
	//if (shell_data->einfo->n_pipes != index)
	if (shell_data->einfo->n_pipes == index)
		close(STDIN_FILENO);
	else
		close(STDOUT_FILENO);
	rl_clear_history();
	free_tokens(shell_data->tokens);
	free_shell_data(shell_data);
	exit(0);
}
