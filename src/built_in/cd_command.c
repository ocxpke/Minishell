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

static int act_pwd_and_oldpwd_env(t_shell_data *shell_data, char *newpwd)
{
	char *old_pwd;

	old_pwd = get_enviroment_value("PWD", shell_data->shell_envi.envp);
	if (!old_pwd)
		return (0);
	old_pwd = ft_strdup(old_pwd);
	modify_value_env_node(&(shell_data->shell_envi), "PWD", newpwd);
	modify_value_env_node(&(shell_data->shell_envi), "OLDPWD", old_pwd);
	free(old_pwd);
	return (1);
}

void	cd_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret)
{
	char	*new_wd;

	*ret = 1;
	//TODO: Pablo la len de cmmd_args
	if (ft_matrix_len((void **) cinfo->cmd_and_args) > 2)
		return (errno = EINVAL ,perror("Too many arguments\n"));
	else if (!cinfo->cmd_and_args[1])
	{
		new_wd = get_enviroment_value("HOME", shell_data->shell_envi.envp);
		if (!new_wd)
			return (errno = ENOENT , perror("HOME not set\n"));
		chdir(new_wd);
		act_pwd_and_oldpwd_env(shell_data, new_wd);
		return;
	}
	chdir(cinfo->cmd_and_args[1]);
	new_wd = getcwd(NULL, 0);
	if (new_wd)
		act_pwd_and_oldpwd_env(shell_data, new_wd);
	free(new_wd);
}
