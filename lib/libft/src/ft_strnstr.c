/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:21:14 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	i = 0;
	while (big[i] && i + little_len <= len)
	{
		if (ft_strncmp(&big[i], little, little_len) == 0)
			return ((char *)&big[i]);
		++i;
	}
	return (NULL);
}
