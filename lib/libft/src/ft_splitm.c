/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:29 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/29 16:36:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Splits a string into substrings based on a set of delimiter
 * characters.
 *
 * This function takes a string `s` and splits it into substrings, storing the
 * substrings in the array `str_cont`. The delimiters are specified in the
 * string `cs`. The number of substrings to be created is specified by
 * `token_count`.
 *
 * @param s The input string to be split.
 * @param str_cont The array to store the resulting substrings.
 * @param cs The string containing delimiter characters.
 * @param token_count The number of substrings to be created.
 * @return A pointer to the array of substrings, or NULL if memory allocation
 *         fails.
 */
static char	**set_substrs(char const *s, char **str_cont, char *cs,
		size_t token_count)
{
	size_t	substr_count;
	size_t	subs_str_len;
	char	*next_t;

	substr_count = 0;
	while (ft_strchr(cs, *s))
		++s;
	while (substr_count < token_count)
	{
		if (*s && ft_strchr(cs, *s) == NULL)
		{
			next_t = ft_strchrm(s, cs);
			subs_str_len = (next_t - s);
			if (!next_t)
				subs_str_len = (ft_strchr(s, '\0') - s);
			str_cont[substr_count] = ft_calloc(subs_str_len + 1, sizeof(char));
			if (!str_cont[substr_count])
				return (NULL);
			ft_strlcpy(str_cont[substr_count], s, subs_str_len + 1);
			s = next_t;
			++substr_count;
		}
		++s;
	}
	return (str_cont);
}

/**
 * Frees a null-terminated array of pointers.
 *
 * This function iterates through each element of the provided array `mtx`,
 * freeing each element individually. After all elements have been freed,
 * the array itself is also freed.
 *
 * @param mtx A null-terminated array of pointers to be freed.
 */
static void	ft_freemtx(void **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		ft_free((void **)&mtx[i++]);
	ft_free((void **)&mtx);
}

char	**ft_splitm(char const *s, char *cs)
{
	size_t	c_count;
	char	**str_cont;

	c_count = ft_strtkns(s, cs);
	str_cont = malloc(sizeof(char *) * (c_count + 1));
	if (!str_cont)
		return (NULL);
	if (!set_substrs(s, str_cont, cs, c_count))
	{
		ft_freemtx((void **)str_cont);
		return (NULL);
	}
	str_cont[c_count] = NULL;
	return (str_cont);
}
