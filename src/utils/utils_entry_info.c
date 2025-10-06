/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_entry_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:52:02 by pablo             #+#    #+#             */
/*   Updated: 2025/09/16 19:33:26 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates and initializes a new t_einfo structure.
 *
 * This function allocates memory for a t_einfo structure and initializes
 * its members to default values:
 *
 *   - input_file, output_file and commands are set to NULL.
 *
 *   - is_append, is_heredoc, and n_pipes are set to -1.
 *
 * @return Pointer to the newly allocated and initialized t_einfo structure,
 *         or NULL if memory allocation fails.
 */
static t_einfo	*initialize_einfo(void)
{
	t_einfo	*einfo;

	einfo = malloc(sizeof(t_einfo));
	if (!einfo)
		return (NULL);
	einfo->input_file = NULL;
	einfo->output_file = NULL;
	einfo->is_append = -1;
	einfo->is_heredoc = -1;
	einfo->n_pipes = -1;
	einfo->commands = NULL;
	einfo->piped_info = NULL;
	return (einfo);
}

/**
 * @brief Sets the input file and heredoc status in the entry info struct.
 *
 * Searches the token list for input redirection tokens. If a standard input
 * redirection ('<') is found, sets the input file path and marks heredoc as
 * not used. If a heredoc redirection ('<<') is found, processes the heredoc,
 * sets the input file path, and marks heredoc as used.
 *
 * @param tokens Pointer to the list of tokens to search for input redirection.
 * @param einfo Pointer to the entry info struct to update.
 */
static void	set_input_file(t_token **tokens, t_einfo *einfo)
{
	char	*route;
	t_token	*extracted;

	extracted = extract_first_type_token(tokens, REDIRECT_IN_ROUTE);
	if (extracted)
	{
		einfo->input_file = extracted->string;
		einfo->is_heredoc = 0;
	}
	else if (extract_first_type_token(tokens, REDIRECT_IN_CHAR_HEREDOC))
	{
		extracted = extract_first_type_token(tokens, HEREDOC_EOF);
		if (extracted)
		{
			ft_get_next_line(-1);
			route = heredoc_behaviour(extracted->string);
			if (route)
			{
				einfo->input_file = route;
				einfo->is_heredoc = 1;
			}
		}
	}
}

/**
 * @brief Sets the output file and append mode in the entry info struct.
 *
 * Examines the token list for output redirection (overwrite or append).
 * If found, extracts the file token and updates `output_file` and
 * `is_append` in the `einfo` struct.
 *
 * @param tokens Pointer to the token list to examine and modify.
 * @param einfo Pointer to the entry info struct to update.
 */
static void	set_output_file(t_token **tokens, t_einfo *einfo)
{
	t_token	*extracted;

	if (extract_first_type_token(tokens, REDIRECT_OUT_CHAR))
	{
		extracted = extract_first_type_token(tokens, REDIRECT_OUT_ROUTE);
		if (extracted)
		{
			einfo->output_file = extracted->string;
			einfo->is_append = 0;
		}
	}
	else if (extract_first_type_token(tokens, REDIRECT_OUT_CHAR_APPEND))
	{
		extracted = extract_first_type_token(tokens, REDIRECT_OUT_ROUTE);
		if (extracted)
		{
			einfo->output_file = extracted->string;
			einfo->is_append = 1;
		}
	}
}

t_einfo	*get_entry_info(t_token **tokens)
{
	t_einfo	*einfo;

	einfo = initialize_einfo();
	if (!einfo)
		return (NULL);
	set_input_file(tokens, einfo);
	set_output_file(tokens, einfo);
	einfo->n_pipes = count_tokens(tokens, PIPE);
	einfo->commands = get_commands(tokens);
	einfo->piped_info = NULL;
	//debug_einfo(einfo);
	return (einfo);
}

void	clean_entry_info(t_einfo **einfo)
{
	int	i;

	if (!einfo || !*einfo)
		return ;
	free_piped_info_list(*einfo);
	ft_free((void **)&((*einfo)->input_file));
	ft_free((void **)&((*einfo)->output_file));
	if ((*einfo)->commands)
	{
		i = 0;
		while ((*einfo)->commands[i])
		{
			ft_matrix_free((void **)(*einfo)->commands[i], 0);
			i++;
		}
		ft_free((void **)&((*einfo)->commands));
	}
	ft_free((void **)einfo);
}
