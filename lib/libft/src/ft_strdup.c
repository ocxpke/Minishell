/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:34:43 by pabmart2          #+#    #+#             */
/*   Updated: 2025/11/12 21:28:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*cpy;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	cpy = ft_calloc(len, sizeof(char));
	if (!cpy)
		return (NULL);
	return (ft_memcpy(cpy, s, len));
}
