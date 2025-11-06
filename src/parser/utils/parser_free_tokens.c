/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:43:53 by pablo             #+#    #+#             */
/*   Updated: 2025/11/03 22:07:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_tokens(t_token ***tokens)
{
	size_t	i;

	if (!tokens || !*tokens)
		return ;
	i = 0;
	while ((*tokens)[i])
	{
		if ((*tokens)[i] && (*tokens)[i]->string)
			free((*tokens)[i]->string);
		if ((*tokens)[i])
		{
			free((*tokens)[i]);
			(*tokens)[i] = NULL;
		}
		i++;
	}
	if (*tokens)
		free(*tokens);
	*tokens = NULL;
}
