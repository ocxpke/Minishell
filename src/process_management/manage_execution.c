/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:02:41 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/09 16:07:58 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_pipes(int pipes[2], int npipes, int pos)
{
	if ((npipes <= 0) || (pos == npipes))
		return ;
	if (pipe(pipes) == -1)
		return ;
}

static void	child_management(t_shell_data *shell_data, int pipes[2],
		int *pipe_aux, int index)
{
	if (check_built_in_name(shell_data->einfo->cinfos[index]))
		exec_subshell(shell_data, pipes, pipe_aux, index);
	else
		child_process(shell_data, pipes, pipe_aux, index);
}

void	execution_cycle(t_shell_data *shell_data)
{
	int	i;
	int	pipes[2];
	int	pipe_aux;

	i = 0;
	pipe_aux = -1;
	while (i < (shell_data->einfo->n_pipes + 1))
	{
		manage_pipes(pipes, shell_data->einfo->n_pipes, i);
		if (!check_if_is_built_in(shell_data, shell_data->einfo->cinfos[i]))
		{
			shell_data->pid_fork = fork();
			if (shell_data->pid_fork == -1)
				exit(EXIT_FAILURE);
			if (shell_data->einfo->n_pipes)
				add_piped_info_node(shell_data, shell_data->pid_fork);
			if (shell_data->pid_fork == 0)
				child_management(shell_data, pipes, &pipe_aux, i);
			else
				parent_process(shell_data, pipes, &pipe_aux, i);
		}
		i++;
	}
}
