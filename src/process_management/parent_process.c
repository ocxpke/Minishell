/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:02:46 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO partir en cachitos, si el comando no existe exit_code=127,
// preguntar a pablo que hace con el manejo de los comandos q no existen
void	parent_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux,
		int index)
{
	t_piped_info	*wait_node;
	int				ret_status;
	char			*exit_code;

	if (shell_data->einfo->n_pipes && (shell_data->einfo->n_pipes != index))
	{
		close(pipes[1]);
		if (*pipe_aux != -1)
			close(*pipe_aux);
		*pipe_aux = dup(pipes[0]);
		close(pipes[0]);
	}else if(shell_data->einfo->n_pipes && (shell_data->einfo->n_pipes == index))
		close(*pipe_aux);
	if (shell_data->einfo->n_pipes)
	{
		if (shell_data->einfo->n_pipes != index)
			return;
		wait_node = shell_data->einfo->piped_info;
		while(wait_node)
		{
			waitpid(wait_node->pid, &ret_status, 0);
			wait_node = wait_node->next;
		}
	}
	else
		waitpid(shell_data->pid_fork, &ret_status, 0);
	if (index == shell_data->einfo->n_pipes)
	{
		exit_code = ft_itoa(WEXITSTATUS(ret_status));
		modify_value_env_node(&(shell_data->shell_envi), "FT_EXIT_ENV", exit_code);
		free(exit_code);
	}
}
