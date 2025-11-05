/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/05 16:54:42 by pablo            ###   ########.fr       */
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
		write(1, cinfo->cmd_and_args[i], ft_strlen(cinfo->cmd_and_args[i]));
		if (cinfo->cmd_and_args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (final_nl)
		write(1, "\n", 1);
}
