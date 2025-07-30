/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:39:57 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Recursively converts an unsigned integer to a string representation
 * in a given base.
 *
 * This function takes an unsigned integer and converts it to a string
 * representation in the specified base. It uses recursion to handle the
 * conversion process.
 *
 * @param un The unsigned integer to be converted.
 * @param base_l The length of the base (e.g., 10 for decimal, 16 for
 * hexadecimal).
 * @param base A string representing the characters used in the base
 * (e.g., "0123456789ABCDEF" for hexadecimal).
 * @param str A pointer to the string where the result will be stored.
 * @return A pointer to the resulting string representation of the number.
 */
static char	*set_n_base(unsigned int un, unsigned int base_l, char *base,
		char *str)
{
	if (un >= base_l)
	{
		str = set_n_base(un / base_l, base_l, base, str);
		set_n_base(un % base_l, base_l, base, ++str);
	}
	if (un < base_l)
		*str = base[un];
	return (str);
}

/**
 * @brief Counts the number of digits required to represent an unsigned integer
 *        in a given base.
 *
 * This function recursively calculates the number of digits needed to represent
 * the given unsigned integer `un` in the specified base `base_l`. It increments
 * the counter for each recursive call until the base condition is met.
 *
 * @param un The unsigned integer to be converted.
 * @param base_l The base in which the number is to be represented.
 * @param counter The current count of digits (initially should be 0).
 * @return The total number of digits required to represent the number
 *         in the given base.
 */
static size_t	count_base_c(unsigned int un, unsigned int base_l,
		size_t counter)
{
	if (un >= base_l)
		return (count_base_c(un / base_l, base_l, ++counter));
	return (counter + 1);
}

char	*ft_uitob(unsigned int nbr, char *base)
{
	size_t	base_l;
	char	*str;

	base_l = ft_strlen(base);
	str = ft_calloc(count_base_c(nbr, base_l, 0) + 1, sizeof(char));
	set_n_base(nbr, base_l, base, str);
	return (str);
}
