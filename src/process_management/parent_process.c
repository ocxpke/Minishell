/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/19 17:39:48 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_recv;

static void	close_fds(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	if (!shell_data->einfo->n_pipes)
		return ;
	if (index != shell_data->einfo->n_pipes)
	{
		close(pipes[1]);
		if (*pipe_aux != -1)
			close(*pipe_aux);
		*pipe_aux = dup(pipes[0]);
		close(pipes[0]);
	}
	else if (index == shell_data->einfo->n_pipes)
		close(*pipe_aux);
}

static void	manage_exit_code(t_shell_data *shell_data, int ret_status,
		int index)
{
	int	exit_num;

	exit_num = 0;
	if (g_signal_recv == SIGINT)
		exit_num = ((128 + SIGINT) % 256);
	else if (WIFEXITED(ret_status))
		exit_num = WEXITSTATUS(ret_status);
	else if (WIFSIGNALED(ret_status))
	{
		exit_num = ((128 + WTERMSIG(ret_status)) % 256);
		if (WTERMSIG(ret_status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		if (WTERMSIG(ret_status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
	if (index == shell_data->einfo->n_pipes)
		modify_exit_status_value(&shell_data->shell_envi, exit_num);
}

void	parent_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_piped_info	*wait_node;
	int				ret_status;

	close_fds(shell_data, pipes, pipe_aux, index);
	signal(SIGINT, SIG_IGN);
	if (shell_data->einfo->n_pipes)
	{
		if (shell_data->einfo->n_pipes != index)
			return ;
		wait_node = shell_data->einfo->piped_info;
		while (wait_node)
		{
			waitpid(wait_node->pid, &ret_status, 0);
			wait_node = wait_node->next;
		}
	}
	else
		waitpid(shell_data->pid_fork, &ret_status, 0);
	signal(SIGINT, sigint_handler);
	manage_exit_code(shell_data, ret_status, index);
}
