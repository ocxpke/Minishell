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

static int redirect_input_built_in(t_cinfo *cinfo, int *save_stdin)
{
	int new_fd;

	if (!cinfo->input_file)
		return (0);
	new_fd = open(cinfo->input_file, O_RDONLY, 0644);
	if (new_fd == -1)
		return (-1);
	*save_stdin = dup(STDIN_FILENO);
	dup2(new_fd, STDIN_FILENO);
	close(new_fd);
	return (1);
}

static int redirect_output_built_in(t_cinfo *cinfo, int *save_stdout)
{
	int new_fd;

	if (!cinfo->output_file)
		return (0);
	if (cinfo->is_append)
		new_fd = open(cinfo->output_file, O_WRONLY | O_CREAT | O_APPEND , 0644);
	else
		new_fd = open(cinfo->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd == -1)
		return (-1);
	*save_stdout = dup(STDOUT_FILENO);
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (1);
}

inline int	check_built_in_name(t_cinfo *cinfo)
{
	if (!ft_strncmp(cinfo->cmd_and_args[0], "exit",
			ft_max_len_str(cinfo->cmd_and_args[0], "exit"))
		|| !ft_strncmp(cinfo->cmd_and_args[0], "pwd",
			ft_max_len_str(cinfo->cmd_and_args[0], "pwd"))
		|| !ft_strncmp(cinfo->cmd_and_args[0], "cd",
			ft_max_len_str(cinfo->cmd_and_args[0], "cd"))
		|| !ft_strncmp(cinfo->cmd_and_args[0], "echo",
			ft_max_len_str(cinfo->cmd_and_args[0], "echo"))
		|| !ft_strncmp(cinfo->cmd_and_args[0], "env",
			ft_max_len_str(cinfo->cmd_and_args[0], "env"))
		|| !ft_strncmp(cinfo->cmd_and_args[0], "export",
			ft_max_len_str(cinfo->cmd_and_args[0], "export"))
		|| !ft_strncmp(cinfo->cmd_and_args[0], "unset",
			ft_max_len_str(cinfo->cmd_and_args[0], "unset")))
		return (1);
	return (0);
}

inline int	exec_built_in(t_shell_data *shell_data, t_cinfo *cinfo)
{
	int		ret;
	size_t	cmd_len;

	cinfo = shell_data->einfo->cinfos[index];
	ret = 0;
	if (!cinfo || !cinfo->cmd_and_args ||!cinfo->cmd_and_args[0])
		return (0);
	cmd_len = ft_strlen(cinfo->cmd_and_args[0]);
	if (!ft_strncmp(cinfo->cmd_and_args[0], "exit", cmd_len))
		exit_cmd(shell_data, cinfo);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "pwd", cmd_len))
		pwd_cmd(&ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "cd", cmd_len))
		cd_cmd(shell_data, cinfo, &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "echo", cmd_len))
		echo_cmd(cinfo, &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "env", cmd_len))
		env_cmd(cinfo, &(shell_data->shell_envi), &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "export", cmd_len))
		export_cmd(shell_data, cinfo, &ret);
	else if (!ft_strncmp(cinfo->cmd_and_args[0], "unset", cmd_len))
		unset_cmd(shell_data, cinfo, &ret);
	return (ret);
}

//TODO funcion que guarde el exit code en la env correspondiente
int	check_if_is_built_in(t_shell_data *shell_data, t_cinfo *cinfo)
{
	int save_stdin;
	int save_stdout;

	save_stdin = -1;
	save_stdout = -1;
	if (shell_data->einfo->n_pipes || !cinfo || !check_built_in_name(cinfo))
		return (0);
	if ((redirect_input_built_in(cinfo, &save_stdin) == -1) || (redirect_output_built_in(cinfo, &save_stdout) == -1))
		return(modify_exit_status_value(&(shell_data->shell_envi), 1), printf("HOLA\n"), 1);
	exec_built_in(shell_data, cinfo);
	if (save_stdin != -1)
	{
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
	}
	if (save_stdout != -1)
	{
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdout);
	}
	return (modify_exit_status_value(&(shell_data->shell_envi), 0), 1);
}
