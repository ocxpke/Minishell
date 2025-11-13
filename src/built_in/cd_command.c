/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:32 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/12 20:33:48 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints an error message for the cd command.
 *
 * This function outputs an error message to stderr, mimicking the
 * format used by bash. The message includes "bash: cd: " followed by
 * the provided path (if not NULL), a colon and space, and the string
 * representation of the current errno value.
 *
 * @param path The path that caused the error, or NULL if no path
 * should be included in the message.
 */
static void	print_cd_error(char *path)
{
	ft_putstr_fd("bash: cd: ", 2);
	if (path)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
}

/**
 * @brief Updates the PWD and OLDPWD environment variables in the shell
 * data.
 *
 * This function retrieves the current value of the PWD environment
 * variable, duplicates it to store as the old PWD, then updates PWD to
 * the new value provided and sets OLDPWD to the duplicated old value.
 * It handles memory management by freeing the duplicated string.
 *
 * @param shell_data Pointer to the shell data structure containing
 * environment variables.
 * @param newpwd The new value to set for the PWD environment variable.
 * @return 1 if the update was successful, 0 if the current PWD could not
 * be retrieved.
 */
static int	act_pwd_and_oldpwd_env(t_shell_data *shell_data, char *newpwd)
{
	char	*old_pwd;

	old_pwd = get_env_value("PWD", shell_data->shell_envi.envp);
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

	*ret = 0;
	if (cinfo->array_size > 2)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		return (*ret = 1, (void)0);
	}
	else if (cinfo->array_size == 1)
	{
		new_wd = get_env_value("HOME", shell_data->shell_envi.envp);
		if (!new_wd)
			return (*ret = 1, errno = ENOENT, print_cd_error(NULL));
		chdir(new_wd);
		act_pwd_and_oldpwd_env(shell_data, new_wd);
		return ;
	}
	if (chdir(cinfo->cmd_and_args[1]))
		return (*ret = 1, print_cd_error(cinfo->cmd_and_args[1]));
	new_wd = getcwd(NULL, 0);
	if (new_wd)
		act_pwd_and_oldpwd_env(shell_data, new_wd);
	free(new_wd);
}
