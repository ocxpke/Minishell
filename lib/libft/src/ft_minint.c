/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:17:34 by pablo             #+#    #+#             */
/*   Updated: 2025/06/13 13:16:15 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_minint(int *array, size_t size)
{
	int		min;
	size_t	i;
	size_t	min_pos;

	min = INT_MAX;
	i = 0;
	min_pos = 0;
	while (i < size)
	{
		if (min > array[i])
		{
			min_pos = i;
			min = array[i];
		}
		++i;
	}
	return (min_pos);
}
