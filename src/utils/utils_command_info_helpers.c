/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_info_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:09:55 by pablo             #+#    #+#             */
/*   Updated: 2025/11/11 18:36:45 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_command(t_token **tokens, int n, int *token_pos)
{
	int	cmd_count;
	int	i;

	cmd_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->token_type == COMMAND_BUILT_IN
			|| tokens[i]->token_type == COMMAND_ROUTE
			|| tokens[i]->token_type == COMMAND_NOT_FOUND)
		{
			if (cmd_count == n)
			{
				if (token_pos != NULL)
					*token_pos = i;
				return (tokens[i]);
			}
			cmd_count++;
		}
		++i;
	}
	if (token_pos != NULL)
		*token_pos = -1;
	return (NULL);
}

int	count_command_args(t_token **tokens, int cmd_pos)
{
	int	args_count;

	args_count = 0;
	++cmd_pos;
	while (tokens[cmd_pos] && tokens[cmd_pos]->token_type != PIPE)
	{
		if (tokens[cmd_pos]->token_type == ARGUMENT)
			args_count++;
		cmd_pos++;
	}
	return (args_count);
}
