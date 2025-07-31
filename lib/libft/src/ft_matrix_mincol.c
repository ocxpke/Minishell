/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mincol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:17:34 by pablo             #+#    #+#             */
/*   Updated: 2025/03/14 17:37:05 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_matrix_mincol(double **array, size_t size, size_t pos)
{
	double	min;
	size_t	i;

	min = DBL_MAX;
	i = 0;
	while (i < size)
	{
		if (min > array[i][pos])
		{
			min = array[i][pos];
		}
		++i;
	}
	return (min);
}
