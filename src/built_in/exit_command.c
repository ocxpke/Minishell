/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:52 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/09 15:59:29 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_is_num(char *first_arg)
{
	if (!first_arg)
		return (1);
	while (*first_arg)
	{
		if (!ft_isdigit(*first_arg))
			return (0);
		first_arg++;
	}
	return (1);
}

void	exit_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret)
{
	int		num_ret;
	char	*exit_env_val;

	if (cinfo->array_size > 2)
		return (*ret = -1, errno = E2BIG, perror("bash: exit"));
	if (!check_is_num(cinfo->cmd_and_args[1]))
		return (*ret = -1, errno = EINVAL, perror("bash: exit"));
	else if (cinfo->array_size == 1)
	{
		exit_env_val = get_enviroment_value("FT_EXIT_ENV",
				shell_data->shell_envi.envp);
		if (!exit_env_val)
			num_ret = ft_atoi(exit_env_val);
		else
			num_ret = 0;
	}
	else
		num_ret = ft_atoi(cinfo->cmd_and_args[1]);
	rl_clear_history();
	free_shell_data(shell_data);
	exit(num_ret % 256);
}
