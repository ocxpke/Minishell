/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shell_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:02:51 by jose-ara          #+#    #+#             */
/*   Updated: 2025/10/20 19:05:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	free_shell_data(t_shell_data *shell_data)
{
	clean_entry_info(&shell_data->einfo);
	free_splitted_string(shell_data->shell_envi.envp_exec);
	free_env_linked_list(&(shell_data->shell_envi.envp));
	free_env_linked_list(&(shell_data->shell_envi.ordered_envp));
	clean_entry_info(&(shell_data->einfo));
}

void	init_shell_data(t_shell_data *shell_data)
{
	shell_data->pid_fork = 0;
	shell_data->tokens = NULL;
	shell_data->shell_envi.envp = NULL;
	shell_data->shell_envi.ordered_envp = NULL;
	shell_data->shell_envi.len_env = 0;
	shell_data->shell_envi.envp_exec = NULL;
	shell_data->einfo = NULL;
	clone_environs(&(shell_data->shell_envi));
}
