/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/08/01 12:55:09 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux, int index)
{

	if (shell_data->einfo->n_pipes > 0)
    {
		close(pipes[1]);
		//Esta puta linea me ha tenido un ratazo
		*pipe_aux = dup(pipes[0]);
        close(pipes[0]);
    }

	// Ctrl+z suspende un proceso-- > implica controol de tareas-- > no hacer nada,no ?
	if (!shell_data->einfo->n_pipes)
		waitpid(shell_data->pid_fork, NULL, 0);
	//Para el wait de las pipes, lista enlazada de pids
	else if (index == shell_data->einfo->n_pipes)
		waitpid(0, NULL, 0);

}
