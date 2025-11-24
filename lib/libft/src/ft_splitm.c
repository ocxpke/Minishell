/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:29 by pabmart2          #+#    #+#             */
/*   Updated: 2025/11/24 21:14:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Splits a string into substrings based on a delimiter
 * charset and stores them in a pre-allocated array.
 *
 * This function processes the input string `s`, skipping any
 * leading delimiters specified in `cs`. It then extracts up to
 * `token_count` substrings, where each substring is delimited by
 * characters in `cs`. Each extracted substring is allocated and
 * copied into the corresponding slot in `str_cont`. If memory
 * allocation fails for any substring, the function returns NULL.
 *
 * @param s The input string to be split.
 * @param str_cont A pre-allocated array of char pointers to store
 * the resulting substrings.
 * @param cs A string containing the delimiter characters.
 * @param token_count The maximum number of substrings to extract.
 *
 * @return A pointer to `str_cont` if successful, or NULL if memory
 * allocation fails.
 *
 * @note The caller is responsible for allocating `str_cont` with at
 * least `token_count` elements. Unused elements in `str_cont`
 * remain NULL.
 */
static char	**set_substrs(char const *s, char **str_cont, char *cs,
		size_t token_count)
{
	size_t	i;
	char	*start;

	i = 0;
	while (*s && ft_strchr(cs, *s))
		++s;
	while (i < token_count)
	{
		if (!*s)
			break ;
		start = (char *)s;
		while (*s && !ft_strchr(cs, *s))
			++s;
		str_cont[i] = ft_calloc((s - start) + 1, sizeof(char));
		if (!str_cont[i])
			return (NULL);
		ft_strlcpy(str_cont[i], start, (s - start) + 1);
		++i;
		while (*s && ft_strchr(cs, *s))
			++s;
	}
	return (str_cont);
}

char	**ft_splitm(char const *s, char *cs)
{
	size_t	c_count;
	char	**str_cont;

	if (!s)
		return (NULL);
	c_count = ft_strtkns(s, cs);
	str_cont = malloc(sizeof(char *) * (c_count + 1));
	if (!str_cont)
		return (NULL);
	if (!set_substrs(s, str_cont, cs, c_count))
	{
		ft_matrix_free((void ***)&str_cont, 0);
		return (NULL);
	}
	str_cont[c_count] = NULL;
	return (str_cont);
}
