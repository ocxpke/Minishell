/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:01:49 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*cpy;

	len = (size_t)(ft_strchr(s, '\0') - s + 1);
	if (n && n < len)
		len = n;
	cpy = malloc(len);
	if (!cpy)
		return (NULL);
	ft_memset(cpy, 0, len);
	ft_strlcat(cpy, s, len);
	return (cpy);
}
