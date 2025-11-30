/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/12 20:33:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_echo_param(t_cinfo *cinfo, int i)
{
	int	j;

	j = 1;
	if(!ft_strncmp(cinfo->cmd_and_args[i], "-n", 2))
	{
		while(cinfo->cmd_and_args[i][j])
		{
			if (cinfo->cmd_and_args[i][j] != 'n')
				return (0);
			j++;
		}
		return (1);
	}
	return (0);
}

void	echo_cmd(t_cinfo *cinfo, int *ret)
{
	int	i;
	int	final_nl;

	i = 1;
	final_nl = 1;
	while (cinfo->cmd_and_args[i] && check_echo_param(cinfo, i))
	{
		final_nl = 0;
		i++;
	}
	while (cinfo->cmd_and_args[i])
	{
		write(STDOUT_FILENO, cinfo->cmd_and_args[i],
			ft_strlen(cinfo->cmd_and_args[i]));
		if (cinfo->cmd_and_args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (final_nl)
		write(STDOUT_FILENO, "\n", 1);
	*ret = 0;
}
