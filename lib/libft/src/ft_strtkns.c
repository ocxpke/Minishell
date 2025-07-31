/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtkns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:18:39 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strtkns(char const *s, char *cs)
{
	size_t	counter;
	int		inside_token;

	counter = 0;
	inside_token = 0;
	while (*s)
	{
		if (ft_strchr(cs, *s) == NULL && !inside_token)
		{
			inside_token = 1;
			++counter;
		}
		else if (ft_strchr(cs, *s) != NULL)
			inside_token = 0;
		++s;
	}
	return (counter);
}
