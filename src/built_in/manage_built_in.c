/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:07 by jose-ara          #+#    #+#             */
/*   Updated: 2025/10/27 19:12:50 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline int	check_built_in_name(t_cinfo *cinfo)
{
	if (ft_strncmp(cinfo->cmd_and_args[0], "exit",
			ft_strlen(cinfo->cmd_and_args[0]))
		|| ft_strncmp(cinfo->cmd_and_args[0], "pwd",
			ft_strlen(cinfo->cmd_and_args[0]))
		|| ft_strncmp(cinfo->cmd_and_args[0], "cd",
			ft_strlen(cinfo->cmd_and_args[0]))
		|| ft_strncmp(cinfo->cmd_and_args[0], "echo",
			ft_strlen(cinfo->cmd_and_args[0]))
		|| ft_strncmp(cinfo->cmd_and_args[0], "env",
			ft_strlen(cinfo->cmd_and_args[0]))
		|| ft_strncmp(cinfo->cmd_and_args[0], "export",
			ft_strlen(cinfo->cmd_and_args[0]))
		|| ft_strncmp(cinfo->cmd_and_args[0], "unset",
			ft_strlen(cinfo->cmd_and_args[0])))
		return (0);
	return (1);
}

/*
	TODO: Esto que coño hace, aqui?
char	*file_of_piped_command(t_shell_data *shell_data, int index)
{
	char	*file_name;

	if (!shell_data->einfo->n_pipes || !check_built_in_name(shell_data))
		return (NULL);
	file_name = generate_cmmd_file_name(index);
	if (!file_name)
		return (0);
	if (!generate_cmmd_file(file_name, shell_data->einfo->cinfos[index]->cmd_and_args[0]))
		return (free(file_name), NULL);
	return (file_name);
}
*/

inline int	check_all_built_in(t_shell_data *shell_data, t_cinfo *cinfo,int index)
{
	int		ret;
	size_t	cmd_len;

	ret = 0;
	if (!cinfo || !cinfo->cmd_and_args ||!cinfo->cmd_and_args[0])
		return (0);
	cmd_len = ft_strlen(cinfo->cmd_and_args[0]);
	if (!ft_strncmp(cinfo->cmd_and_args[0], "exit", cmd_len))
		exit_cmd(shell_data);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "pwd", cmd_len))
		pwd_cmd(&ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "cd", cmd_len))
		cd_cmd(shell_data, &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "echo", cmd_len))
		echo_cmd(shell_data, &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "env", cmd_len))
		env_cmd(&(shell_data->shell_envi), &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "export", cmd_len))
		export_cmd(shell_data, &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "unset", cmd_len))
		unset_cmd(shell_data, &ret);
	return (ret);
}


int	check_if_is_built_in(t_shell_data *shell_data, int index)
{
	if (shell_data->einfo->n_pipes || !shell_data->einfo->cinfos)
		return (0);
	return (check_all_built_in(shell_data, shell_data->einfo->cinfos[index], index));
}
