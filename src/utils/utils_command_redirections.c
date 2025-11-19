/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:45:12 by pablo             #+#    #+#             */
/*   Updated: 2025/11/19 18:13:40 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_recv;

/**
 * @brief Validates the presence and positioning of heredoc tokens in a token
 * list.
 *
 * This function checks for a heredoc redirection token
 * (REDIRECT_IN_CHAR_HEREDOC) in the provided token list and ensures it
 * is followed by a delimiter token (HEREDOC_EOF). It also verifies
 * that both tokens appear before any pipe token if a pipe is
 * specified, to maintain proper command structure.
 *
 * @param tokens A pointer to the array of tokens to search in.
 * @param pipe An optional pointer to a pipe token; if provided,
 *             heredoc and delimiter must precede it.
 * @param heredoc A pointer to a pointer where the found heredoc token
 *                will be stored.
 * @param delimiter A pointer to a pointer where the found delimiter
 *                  token will be stored.
 * @return 1 if valid heredoc tokens are found and positioned
 *         correctly, 0 otherwise.
 */
static int	validate_heredoc_tokens(t_token **tokens, t_token **pipe,
		t_token ***heredoc, t_token ***delimiter)
{
	*heredoc = extract_first_type_token(tokens, REDIRECT_IN_CHAR_HEREDOC);
	if (!*heredoc || (pipe && *heredoc >= pipe))
		return (0);
	*delimiter = extract_first_type_token(*heredoc + 1, HEREDOC_EOF);
	if (!*delimiter || (pipe && *delimiter >= pipe))
		return (0);
	return (1);
}

/**
 * @brief Handles the interruption of a heredoc input process.
 *
 * This function is called when a heredoc operation is interrupted
 * (e.g., by a signal like SIGINT). It frees the current route string,
 * writes a newline to standard output to maintain terminal formatting,
 * and returns an empty string to indicate the end of the heredoc input.
 *
 * @param route The current route string to be freed and reset.
 * @return A newly allocated empty string representing the terminated
 * heredoc input.
 */
static char	*handle_heredoc_interrupt(char *route)
{
	ft_free((void **)&route);
	write(STDOUT_FILENO, "\n", 1);
	route = ft_strdup("");
	return (route);
}

/**
 * @brief Sets up the heredoc input file for command redirection.
 *
 * This function validates the heredoc tokens, processes the heredoc
 * behavior to generate a temporary file route, handles potential
 * interruptions (e.g., SIGINT), and assigns the route to the command
 * info structure if successful.
 *
 * @param tokens Pointer to the array of tokens to process.
 * @param cinfo Pointer to the command info structure to update with
 * input file details.
 * @param pipe Pointer to the pipe token for validation context.
 * @return 0 on success, 1 on failure (e.g., validation error, heredoc
 * error, or interruption).
 */
static int	set_heredoc_input_file(t_token **tokens, t_cinfo *cinfo,
		t_token **pipe)
{
	char	*route;
	t_token	**heredoc;
	t_token	**delimiter;

	if (!validate_heredoc_tokens(tokens, pipe, &heredoc, &delimiter))
		return (0);
	ft_get_next_line(-1);
	if (heredoc_behaviour((*delimiter)->string, &route) == HEREDOC_ERROR)
	{
		ft_free((void **)&route);
		return (1);
	}
	if (g_signal_recv == SIGINT)
		route = handle_heredoc_interrupt(route);
	if (!route)
		return (1);
	cinfo->input_file = route;
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
