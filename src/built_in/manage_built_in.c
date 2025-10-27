/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:07 by jose-ara          #+#    #+#             */
/*   Updated: 2025/10/27 10:33:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline int	check_built_in_name(t_shell_data *shell_data)
{
	if (ft_strncmp(shell_data->tokens[0]->string, "exit",
			ft_strlen(shell_data->tokens[0]->string))
		|| ft_strncmp(shell_data->tokens[0]->string, "pwd",
			ft_strlen(shell_data->tokens[0]->string))
		|| ft_strncmp(shell_data->tokens[0]->string, "cd",
			ft_strlen(shell_data->tokens[0]->string))
		|| ft_strncmp(shell_data->tokens[0]->string, "echo",
			ft_strlen(shell_data->tokens[0]->string))
		|| ft_strncmp(shell_data->tokens[0]->string, "env",
			ft_strlen(shell_data->tokens[0]->string))
		|| ft_strncmp(shell_data->tokens[0]->string, "export",
			ft_strlen(shell_data->tokens[0]->string))
		|| ft_strncmp(shell_data->tokens[0]->string, "unset",
			ft_strlen(shell_data->tokens[0]->string)))
		return (0);
	return (1);
}

char	*file_of_piped_command(t_shell_data *shell_data, int index)
{
	char	*file_name;

	if (!shell_data->einfo->n_pipes || !check_built_in_name(shell_data))
		return (NULL);
	file_name = generate_cmmd_file_name(index);
	if (!file_name)
		return (0);
	if (!generate_cmmd_file(file_name, shell_data->einfo->cinfos[index]->command))
	//if (!generate_cmmd_file(file_name, shell_data->einfo->commands[index][0]))
		return (free(file_name), NULL);
	return (file_name);
}

inline int	check_all_built_in(t_shell_data *shell_data, int index)
{
	int		ret;
	size_t	cmd_len;
	t_cinfo	*cinfo;

	cinfo = shell_data->einfo->cinfos[index];
	ret = 0;
	if (!cinfo || !cinfo->command)
		return (1);
	cmd_len = ft_strlen(cinfo->command);
	if (!ft_strncmp(cinfo->command, "exit", cmd_len))
		exit_cmd(shell_data);
	else if (!ft_strncmp(cinfo->command, "pwd", cmd_len))
		pwd_cmd(&ret);
	else if (!ft_strncmp(cinfo->command, "cd", cmd_len))
		cd_cmd(shell_data, &ret);
	else if (!ft_strncmp(cinfo->command, "echo", cmd_len))
		echo_cmd(shell_data, &ret);
	else if (!ft_strncmp(cinfo->command, "env", cmd_len))
		env_cmd(&(shell_data->shell_envi), &ret);
	else if (!ft_strncmp(cinfo->command, "export", cmd_len))
		export_cmd(shell_data, &ret);
	else if (!ft_strncmp(cinfo->command, "unset", cmd_len))
		unset_cmd(shell_data, &ret);
	return (ret);
}


int	check_if_is_built_in(t_shell_data *shell_data, int index)
{
	if (shell_data->einfo->n_pipes || !shell_data->einfo->cinfos[index]->command)
		return (0);
	return (check_all_built_in(shell_data, index));
}
