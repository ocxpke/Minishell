/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:45:12 by pablo             #+#    #+#             */
/*   Updated: 2025/11/17 18:53:28 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets up the input file for a heredoc redirection in the
 * command info structure.
 *
 * This function extracts the heredoc redirection token and its
 * delimiter from the token list, generates a temporary file path
 * for the heredoc content, and assigns it to the command info.
 * It ensures that the heredoc is within the bounds of the pipe
 * if specified.
 *
 * @param tokens Pointer to the array of tokens to process.
 * @param cinfo Pointer to the command info structure where the
 * input file will be set.
 * @param pipe Pointer to the pipe token to limit the search
 * scope (can be NULL).
 * @return 0 on success, 1 on failure (e.g., memory allocation
 * error or invalid setup).
 */
static int	set_heredoc_input_file(t_token **tokens, t_cinfo *cinfo,
		t_token **pipe)
{
	char	*route;
	t_token	**heredoc;
	t_token	**delimiter;

	heredoc = extract_first_type_token(tokens, REDIRECT_IN_CHAR_HEREDOC);
	if (!heredoc || (pipe && heredoc >= pipe))
		return (0);
	delimiter = extract_first_type_token(heredoc + 1, HEREDOC_EOF);
	if (!delimiter || (pipe && delimiter >= pipe))
		return (0);
	ft_get_next_line(-1);
	if (heredoc_behaviour((*delimiter)->string, &route) != HEREDOC_SUCCESS)
	{
		ft_free((void **)&route);
		return (1);
	}
	if (!route)
		return (1);
	cinfo->input_file = route;
	if (!cinfo->input_file)
		return (1);
	cinfo->is_heredoc = 1;
	return (0);
}

int	set_command_input_file(t_token **tokens, t_cinfo *cinfo, t_token **pipe)
{
	t_token	**route;

	route = extract_first_type_token(tokens, REDIRECT_IN_ROUTE);
	if (route && (!pipe || route < pipe))
	{
		cinfo->input_file = ft_strdup((*route)->string);
		if (!cinfo->input_file)
			return (1);
		cinfo->is_heredoc = 0;
		return (0);
	}
	return (set_heredoc_input_file(tokens, cinfo, pipe));
}

int	set_command_output_file(t_token **tokens, t_cinfo *cinfo, t_token **pipe)
{
	t_token	**redir;
	t_token	**route;

	route = NULL;
	redir = extract_first_type_token(tokens, REDIRECT_OUT_CHAR);
	if (redir && (!pipe || redir < pipe))
		route = extract_first_type_token(redir + 1, REDIRECT_OUT_ROUTE);
	if (!route || (pipe && route >= pipe))
	{
		redir = extract_first_type_token(tokens, REDIRECT_OUT_CHAR_APPEND);
		if (redir && (!pipe || redir < pipe))
			route = extract_first_type_token(redir + 1, REDIRECT_OUT_ROUTE);
		if (!route || (pipe && route >= pipe))
			return (0);
		cinfo->is_append = 1;
	}
	else
		cinfo->is_append = 0;
	cinfo->output_file = ft_strdup((*route)->string);
	if (!cinfo->output_file)
		return (1);
	return (0);
}
