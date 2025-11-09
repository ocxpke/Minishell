/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extract_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:30:00 by pablo             #+#    #+#             */
/*   Updated: 2025/11/09 16:08:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*extract_first_type_token(t_token **tokens, t_ttype type)
{
	while (*tokens)
	{
		if ((*tokens)->token_type == type)
			return (*tokens);
		++tokens;
	}
	return (NULL);
}

t_token	**find_next_pipe_pos_after_command(t_token **tokens)
{
	t_token	**temp;

	if (!tokens || !*tokens)
		return (NULL);
	temp = tokens;
	while (*temp)
	{
		if ((*temp)->token_type == PIPE && *temp != *tokens)
			return (temp);
		temp++;
	}
	return (NULL);
}
