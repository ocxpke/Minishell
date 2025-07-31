/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_maxcol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:17:34 by pablo             #+#    #+#             */
/*   Updated: 2025/03/14 17:37:03 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_matrix_maxcol(double **array, size_t size, size_t pos)
{
	double	max;
	size_t	i;

	max = DBL_MIN;
	i = 0;
	while (i < size)
	{
		if (max < array[i][pos])
		{
			max = array[i][pos];
		}
		++i;
	}
	return (max);
}
