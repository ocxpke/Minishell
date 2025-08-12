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

extern sig_atomic_t signal_recv;

void	child_process(t_shell_data *shell_data)
{
	free_splitted_string(shell_data->shell_envi.envp_exec);
	generate_exec_envp(&(shell_data->shell_envi));
	restore_terminal_signals();
	if (shell_data->command_exec && shell_data->command_exec[0] != NULL)
		execve(shell_data->command_exec[0], shell_data->command_exec, shell_data->shell_envi.envp_exec);
	free_splitted_string(shell_data->command_exec);
	rl_clear_history();
	free_tokens(shell_data->tokens);
	free_shell_data(shell_data);
	exit(EXIT_FAILURE);
}
