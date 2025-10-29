/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extract_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:30:00 by pablo             #+#    #+#             */
/*   Updated: 2025/10/28 18:11:14 by pablo            ###   ########.fr       */
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
