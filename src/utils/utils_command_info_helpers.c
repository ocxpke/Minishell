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

/**
 * @brief Finds the start position of the pipeline containing the given command.
 *
 * Searches backwards from token_pos to find the previous PIPE token or the
 * beginning of the token array. Returns the position right after the pipe
 * (start of current pipeline) or 0 if no pipe is found.
 *
 * @param tokens Array of token pointers.
 * @param token_pos Position of the command token.
 * @return Position of the start of the current pipeline.
 */
int	find_pipeline_start(t_token **tokens, int token_pos)
{
	int	i;

	i = token_pos - 1;
	while (i >= 0)
	{
		if (tokens[i]->token_type == PIPE)
			return (i + 1);
		i--;
	}
	return (0);
}

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
