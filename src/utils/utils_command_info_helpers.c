/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_info_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:09:55 by pablo             #+#    #+#             */
/*   Updated: 2025/11/03 21:52:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_command_output_file(t_token **tokens, t_cinfo *cinfo, t_token *pipe)
{
	t_token	*extracted;

	if (extract_first_type_token(tokens, REDIRECT_OUT_CHAR))
	{
		extracted = extract_first_type_token(tokens, REDIRECT_OUT_ROUTE);
		if (extracted && (!pipe || pipe > extracted))
		{
			cinfo->output_file = ft_strdup(extracted->string);
			if (!cinfo->output_file)
				return (1);
			cinfo->is_append = 0;
		}
	}
	else if (extract_first_type_token(tokens, REDIRECT_OUT_CHAR_APPEND))
	{
		extracted = extract_first_type_token(tokens, REDIRECT_OUT_ROUTE);
		if (extracted && (!pipe || pipe > extracted))
		{
			cinfo->output_file = ft_strdup(extracted->string);
			if (!cinfo->output_file)
				return (1);
			cinfo->is_append = 1;
		}
	}
	return (0);
}

/**
 * @brief Sets the heredoc input file for the command info structure.
 *
 * This function processes tokens to extract heredoc-related information.
 * It looks for a heredoc redirect token, then extracts the EOF delimiter,
 * and generates a temporary file path for the heredoc content.
 * If successful, it sets the input file in the command info and marks it as
 * a heredoc.
 *
 * @param tokens A pointer to the token list, which may be modified during
 * extraction.
 * @param cinfo A pointer to the command info structure where the input file
 * and heredoc flag are set.
 *
 * @return 0 on success, 1 on memory allocation failure.
 */
static int	set_heredoc_input_file(t_token **tokens, t_cinfo *cinfo)
{
	char	*route;
	t_token	*extracted;

	if (extract_first_type_token(tokens, REDIRECT_IN_CHAR_HEREDOC))
	{
		extracted = extract_first_type_token(tokens + 1, HEREDOC_EOF);
		if (extracted)
		{
			ft_get_next_line(-1);
			route = heredoc_behaviour(extracted->string);
			if (route)
			{
				cinfo->input_file = route;
				if (!cinfo->input_file)
					return (1);
				cinfo->is_heredoc = 1;
			}
		}
	}
	return (0);
}

int	set_command_input_file(t_token **tokens, t_cinfo *cinfo, t_token *pipe)
{
	t_token	*extracted;

	extracted = extract_first_type_token(tokens, REDIRECT_IN_ROUTE);
	if (extracted && (!pipe || pipe > extracted))
	{
		cinfo->input_file = ft_strdup(extracted->string);
		if (!cinfo->input_file)
			return (1);
		cinfo->is_heredoc = 0;
	}
	else if (set_heredoc_input_file(tokens, cinfo) == 1)
		return (1);
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
	while (tokens[cmd_pos] && tokens[cmd_pos]->token_type == ARGUMENT)
	{
		args_count++;
		cmd_pos++;
	}
	return (args_count);
}
