/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:40:58 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of digits in an integer.
 *
 * This function takes an integer as input and returns the number of digits
 * in that integer. If the input integer is 0, the function returns 1.
 *
 * @param n The integer whose digits are to be counted.
 * @return The number of digits in the integer.
 */
static int	count_digits(int n)
{
	int	counter;

	if (n == 0)
		return (1);
	counter = 0;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

/**
 * @brief Converts an integer to a string representation.
 *
 * This function takes an integer `n` and converts it to its string
 * representation, storing the result in the provided `str` buffer.
 * The length of the buffer is specified by `len`.
 *
 *
 * @param str A pointer to the buffer where the string representation will be
 *            stored.
 * @param n The integer to be converted to a string.
 * @param len The length of the buffer.
 * @return A pointer to the resulting string.
 */
static char	*set_numbers(char *str, int n, size_t len)
{
	unsigned int	unsigned_n;

	if (n == 0)
	{
		*str = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
	{
		unsigned_n = (unsigned int)n * -1;
		while (len > 1)
		{
			str[--len] = unsigned_n % 10 + '0';
			unsigned_n /= 10;
		}
		str[0] = '-';
		return (str);
	}
	while (len > 0)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = count_digits(n);
	if (n < 0)
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (set_numbers(str, n, len));
}
