/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:00:42 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_shell_data *shell_data, int *ret)
{
	int	i;

	i = 1;
	*ret = 1;
	while (shell_data->tokens[i])
	{
		write(1, shell_data->tokens[i]->string,
			ft_strlen(shell_data->tokens[i]->string));
		if (shell_data->tokens[i + 1])
			write(1, " ", 1);
		i++;
	}
}
