/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:04:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/08/01 13:17:45 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process(t_token **tokens, char **get_full_cmd, char **envp)
{
	// Creo que necesitamos env por que nos pueden pasar las cosas sin
	// variables de entornos o variables de entorono modificadas
	// restore_terminal_signals();
	if (get_full_cmd[0] != NULL)
		execve(get_full_cmd[0], get_full_cmd, envp);
	free_full_command(get_full_cmd);
	exit(EXIT_FAILURE);
}
