/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:07 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 20:08:50 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline int	check_built_in_name(t_shell_data *shell_data, int index)
{
	if (!ft_strncmp(shell_data->einfo->commands[index][0], "exit",
			ft_strlen(shell_data->einfo->commands[index][0]))
		|| !ft_strncmp(shell_data->einfo->commands[index][0], "pwd",
			ft_strlen(shell_data->einfo->commands[index][0]))
		|| !ft_strncmp(shell_data->einfo->commands[index][0], "cd",
			ft_strlen(shell_data->einfo->commands[index][0]))
		|| !ft_strncmp(shell_data->einfo->commands[index][0], "echo",
			ft_strlen(shell_data->einfo->commands[index][0]))
		|| !ft_strncmp(shell_data->einfo->commands[index][0], "env",
			ft_strlen(shell_data->einfo->commands[index][0]))
		|| !ft_strncmp(shell_data->einfo->commands[index][0], "export",
			ft_strlen(shell_data->einfo->commands[index][0]))
		|| !ft_strncmp(shell_data->einfo->commands[index][0], "unset",
			ft_strlen(shell_data->einfo->commands[index][0])))
		return (1);
	return (0);
}

inline int	check_all_built_in(t_shell_data *shell_data, int index)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(shell_data->einfo->commands[index][0], "exit",
			ft_strlen(shell_data->einfo->commands[index][0])))
		exit_cmd(shell_data);
	else if (!ft_strncmp(shell_data->einfo->commands[index][0], "pwd",
			ft_strlen(shell_data->einfo->commands[index][0])))
		pwd_cmd(&ret);
	else if (!ft_strncmp(shell_data->einfo->commands[index][0], "cd",
			ft_strlen(shell_data->einfo->commands[index][0])))
		cd_cmd(shell_data, &ret);
	else if (!ft_strncmp(shell_data->einfo->commands[index][0], "echo",
			ft_strlen(shell_data->einfo->commands[index][0])))
		echo_cmd(shell_data, &ret);
	else if (!ft_strncmp(shell_data->einfo->commands[index][0], "env",
			ft_strlen(shell_data->einfo->commands[index][0])))
		env_cmd(&(shell_data->shell_envi), &ret);
	else if (!ft_strncmp(shell_data->einfo->commands[index][0], "export",
			ft_strlen(shell_data->einfo->commands[index][0])))
		export_cmd(shell_data, &ret);
	else if (!ft_strncmp(shell_data->einfo->commands[index][0], "unset",
			ft_strlen(shell_data->einfo->commands[index][0])))
		unset_cmd(shell_data, &ret);
	return (ret);
}

int	check_if_is_built_in(t_shell_data *shell_data, int index)
{
	if (shell_data->einfo->n_pipes || !shell_data->einfo->commands[index])
		return (0);
	return (check_all_built_in(shell_data, index));
}
