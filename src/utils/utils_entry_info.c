/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_entry_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:52:02 by pablo             #+#    #+#             */
/*   Updated: 2025/11/21 16:34:20 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_einfo	*initialize_einfo(void)
{
	t_einfo	*einfo;

	einfo = malloc(sizeof(t_einfo));
	if (!einfo)
		return (NULL);
	einfo->n_pipes = -1;
	einfo->cinfos = NULL;
	einfo->piped_info = NULL;
	return (einfo);
}

/**
 * @brief Counts the number of PIPE tokens in the token array,
 * adjusting for pipes at the start or end.
 *
 * This function iterates through the provided token array to count
 * occurrences of PIPE tokens. It then decrements the count if the
 * first token is a PIPE or if the last token is a PIPE, effectively
 * normalizing the pipe count for shell command parsing purposes.
 *
 * @param tokens A null-terminated array of pointers to t_token
 * structures.
 * @return The adjusted count of PIPE tokens.
 */
static int	get_n_pipes(t_token **tokens)
{
	int		n_pipes;
	size_t	len;

	n_pipes = count_tokens(tokens, PIPE);
	if (tokens[0] && tokens[0]->token_type == PIPE)
		--n_pipes;
	len = ft_matrix_len((void **)tokens);
	if (len > 0 && tokens[len - 1]->token_type == PIPE)
		--n_pipes;
	return (n_pipes);
}

int	get_entry_info(t_token **tokens, t_einfo *einfo)
{
	int	ret;

	ret = set_cinfos(tokens, einfo);
	if (ret != 0)
		return (free_tokens(&tokens), ret);
	einfo->n_pipes = get_n_pipes(tokens);
	einfo->piped_info = NULL;
	free_tokens(&tokens);
	return (0);
}

void	clean_entry_info(t_einfo **einfo)
{
	if (!einfo || !*einfo)
		return ;
	if ((*einfo)->cinfos)
		clean_cinfos((*einfo)->cinfos);
	if ((*einfo)->piped_info)
		free_piped_info_list(*einfo);
	ft_free((void **)einfo);
}
