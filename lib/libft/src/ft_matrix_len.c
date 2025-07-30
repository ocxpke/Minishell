/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:17:34 by pablo             #+#    #+#             */
/*   Updated: 2025/03/14 17:37:01 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of a null-terminated array of pointers.
 *
 * This function iterates through the array of pointers until it encounters
 * a null pointer, counting the number of elements in the array.
 *
 * @param array A null-terminated array of pointers.
 * @return The number of elements in the array, excluding the null pointer.
 */
size_t	ft_matrix_len(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		++i;
	if (i > 0)
		return (i);
	return (0);
}
