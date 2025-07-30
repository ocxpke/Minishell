/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mindbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:17:34 by pablo             #+#    #+#             */
/*   Updated: 2025/03/14 17:37:07 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_mindbl(double *array, size_t size)
{
	double	min;
	size_t	i;
	size_t	min_pos;

	min = DBL_MAX;
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
