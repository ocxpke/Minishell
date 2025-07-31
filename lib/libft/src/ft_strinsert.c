/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:23:29 by pablo             #+#    #+#             */
/*   Updated: 2025/07/28 15:26:00 by pablo            ###   ########.fr       */
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
	right = ft_strdup(end_pos);
	tmp = ft_strjoin(left, insert);
	free(left);
	result = ft_strjoin(tmp, right);
	free (right);
	free(tmp);
	return (result);
}
