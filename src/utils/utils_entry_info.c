/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_entry_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:52:02 by pablo             #+#    #+#             */
/*   Updated: 2025/11/03 22:05:06 by pablo            ###   ########.fr       */
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
	einfo->n_pipes = -1;
	einfo->cinfos = NULL;
	return (einfo);
}

t_einfo	*get_entry_info(t_token **tokens)
{
	t_einfo	*einfo;

	einfo = initialize_einfo();
	if (!einfo)
		return (NULL);
	set_cinfos(tokens, einfo);
	if (!einfo->cinfos)
		return (clean_entry_info(&einfo), NULL);
	einfo->n_pipes = count_tokens(tokens, PIPE);
	einfo->piped_info = NULL;
	free_tokens(&tokens);
	return (einfo);
}

void	clean_entry_info(t_einfo **einfo)
{
	if (!einfo || !*einfo)
		return ;
	if ((*einfo)->cinfos)
		clean_cinfos((*einfo)->cinfos);
	ft_free((void **)einfo);
}
