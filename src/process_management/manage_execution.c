/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:02:41 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:02:42 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_pipes(int pipes[2], int npipes, int pos)
{
	if (npipes <= 0 || pos == npipes)
		return ;
	if (pipe(pipes) == -1)
		return ;
}

void	execution_cycle(t_shell_data *shell_data)
{
	int	i;
	int	pipes[2];
	int	pipe_aux;

	i = 0;
	pipe_aux = -1;
	// Le doy una vuelta?
	while (i < (shell_data->einfo->n_pipes + 1))
	{
		manage_pipes(pipes, shell_data->einfo->n_pipes, i);
		if (!check_if_is_built_in(shell_data, i))
		{
			shell_data->pid_fork = fork();
			if (shell_data->pid_fork == -1)
				exit(EXIT_FAILURE);
			if (shell_data->einfo->n_pipes)
				add_piped_info_node(shell_data, shell_data->pid_fork,
					file_of_piped_command(shell_data, i));
			if (shell_data->pid_fork == 0)
			{
				// Todo
				if (0 && check_built_in_name(shell_data))
					exec_subshell(shell_data, pipes, &pipe_aux, i);
				else
					child_process(shell_data, pipes, &pipe_aux, i);
			}
			else
				parent_process(shell_data, pipes, &pipe_aux, i);
			// Ver que coño estoy haciendo
		}
		i++;
	}
}
