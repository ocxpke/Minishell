/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:32 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/09 15:58:48 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	act_pwd_and_oldpwd_env(t_shell_data *shell_data, char *newpwd)
{
	char	*old_pwd;

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
	if (cinfo->array_size > 2)
		return (*ret = -1, errno = EINVAL, perror("bash: cd"));
	else if (cinfo->array_size == 1)
	{
		new_wd = get_enviroment_value("HOME", shell_data->shell_envi.envp);
		if (!new_wd)
			return (*ret = -1, errno = ENOENT, perror("HOME not set"));
		chdir(new_wd);
		act_pwd_and_oldpwd_env(shell_data, new_wd);
		return ;
	}
	if (chdir(cinfo->cmd_and_args[1]))
		return (*ret = -1, perror("bash: cd"));
	new_wd = getcwd(NULL, 0);
	if (new_wd)
		act_pwd_and_oldpwd_env(shell_data, new_wd);
	free(new_wd);
}
