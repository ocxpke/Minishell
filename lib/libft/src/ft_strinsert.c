/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:23:29 by pablo             #+#    #+#             */
/*   Updated: 2025/10/26 14:08:17 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *src, char *start_pos, char *end_pos, char *insert)
{
	char	*left;
	char	*right;
	char	*tmp;
	char	*result;

	left = ft_strndup(src, start_pos - src + 1);
	if (!left)
		return (NULL);
	right = ft_strdup(end_pos);
	if (!right)
		return (free(left), NULL);
	tmp = ft_strjoin(left, insert);
	if (!tmp)
		return (free(left), free(right), NULL);
	result = ft_strjoin(tmp, right);
	free(left);
	free(right);
	free(tmp);
	return (result);
}
