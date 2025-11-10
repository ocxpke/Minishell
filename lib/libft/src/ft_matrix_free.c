/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/02/07 13:17:34 by pablo             #+#    #+#             */
/*   Updated: 2025/06/13 13:13:51 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_matrix_free(void ***array, size_t size)
{
	size_t i;

	if (!array || !*array)
		return ;
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
