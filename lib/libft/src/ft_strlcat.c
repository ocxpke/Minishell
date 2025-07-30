/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:17:08 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/31 22:05:03 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	src_i;

	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	if (size <= dst_length)
		return (size + src_length);
	src_i = 0;
	while (src[src_i] && (src_i + dst_length) < (size - 1))
	{
		dst[dst_length + src_i] = src[src_i];
		src_i++;
	}
	dst[dst_length + src_i] = '\0';
	return (dst_length + src_length);
}
