/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/10 18:33:25 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parent_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_piped_info	*wait_node;
	int				ret_status;

	close_fds(shell_data, pipes, pipe_aux, index);
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
	if (index == shell_data->einfo->n_pipes)
		modify_exit_status_value(&shell_data->shell_envi,
			WEXITSTATUS(ret_status));
}
