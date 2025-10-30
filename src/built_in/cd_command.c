/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:32 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:00:36 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret)
{
	char	*home;

	*ret = 1;
	//TODO: Pablo la len de cmmd_args
	//Esto peta
	if (cinfo->cmd_and_args[2])
		return (errno = EINVAL ,perror("Too many arguments\n"));
	else if (!cinfo->cmd_and_args[1])
	{
		home = get_enviroment_value("HOME", shell_data->shell_envi.envp);
		if (!home)
			return (errno = ENOENT , perror("HOME not set\n"));
		else
			chdir(home);
		//TODO: actualizar el valor de pwd;
	}

	chdir(shell_data->tokens[1]->string);
}
