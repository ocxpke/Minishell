/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:17:34 by pablo             #+#    #+#             */
/*   Updated: 2025/06/13 13:13:51 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a null-terminated array of pointers and sets the array pointer to NULL.
 *
 * This function frees each element of the array using ft_free, then frees the array itself,
 * and finally sets the provided pointer to NULL to prevent dangling pointers.
 *
 * @param array A pointer to the array pointer to be freed and set to NULL.
 * @param size The size of the array. If 0, assumes null-terminated array.
 */
void	ft_matrix_free(void ***array, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size)
		{
			ft_free((void **)&(*array)[i]);
			++i;
		}
	}
	else
	{
		while ((*array)[i])
		{
			ft_free((void **)&(*array)[i]);
			++i;
		}
	}
	ft_free((void **)array);
	*array = NULL;
}
