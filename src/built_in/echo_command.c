/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/11 17:59:59 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_cinfo *cinfo, int *ret)
{
	int	i;
	int	final_nl;

	*ret = 1;
	i = 1;
	final_nl = 1;
	if (cinfo->cmd_and_args[i] && !ft_strncmp(cinfo->cmd_and_args[i], "-n",
			ft_max_len_str(cinfo->cmd_and_args[i], "-n")))
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
}
