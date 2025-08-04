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

void	parent_process(pid_t pid_fork, char **get_full_cmd)
{
	// Ctrl+z suspende un proceso-- > implica controol de tareas-- > no hacer nada,no ?
	waitpid(pid_fork, NULL, 0);
	free_full_command(get_full_cmd);
}
