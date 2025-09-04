/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:51:20 by pablo             #+#    #+#             */
/*   Updated: 2025/08/25 14:07:40 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_tokens(t_token **tokens, t_ttype type)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->token_type == type)
			++count;
		++i;
	}
	return (count);
}
