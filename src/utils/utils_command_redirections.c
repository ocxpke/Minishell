/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:45:12 by pablo             #+#    #+#             */
/*   Updated: 2025/11/10 17:18:57 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_heredoc_input_file(t_token **tokens, t_cinfo *cinfo)
{
	char	*route;
	t_token	**heredoc;
	t_token	**delimiter;

	heredoc = extract_first_type_token(tokens, REDIRECT_IN_CHAR_HEREDOC);
	if (!heredoc)
		return (0);
	delimiter = extract_first_type_token(heredoc + 1, HEREDOC_EOF);
	if (!delimiter)
		return (0);
	ft_get_next_line(-1);
	route = heredoc_behaviour((*delimiter)->string);
	if (!route)
		return (0);
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
	return (set_heredoc_input_file(tokens, cinfo));
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
