/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:29 by pabmart2          #+#    #+#             */
/*   Updated: 2025/11/24 21:20:18 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Splits the input string into substrings based on a
 * delimiter and stores them in the provided array.
 *
 * This function processes the string `s` to extract substrings
 * separated by the character `c`. It skips leading delimiters,
 * then for each of the `token_count` tokens, it allocates memory
 * for the substring, copies it into the `str_cont` array, and
 * skips trailing delimiters. If memory allocation fails, it
 * returns NULL.
 *
 * @param s The input string to split.
 * @param str_cont The array of strings where substrings will be
 * stored.
 * @param c The delimiter character used to split the string.
 * @param token_count The number of substrings to extract.
 * @return A pointer to the `str_cont` array on success, or NULL
 * on memory allocation failure.
 */
static char	**set_substrs(char const *s, char **str_cont, char c,
		size_t token_count)
{
	size_t	i;
	char	*start;

	i = 0;
	while (*s && *s == c)
		++s;
	while (i < token_count)
	{
		if (!*s)
			break ;
		start = (char *)s;
		while (*s && *s != c)
			++s;
		str_cont[i] = ft_calloc((s - start) + 1, sizeof(char));
		if (!str_cont[i])
			return (NULL);
		ft_strlcpy(str_cont[i], start, (s - start) + 1);
		++i;
		while (*s && *s == c)
			++s;
	}
	return (str_cont);
}
/**
 * @brief Counts the number of tokens in a string separated by a given
 * delimiter.
 *
 * This function iterates through the input string `s` and counts the number of
 * tokens separated by the character `c`. A token is defined as a contiguous
 * sequence of characters that are not the delimiter `c`.
 *
 * @param s The input string to be tokenized.
 * @param c The delimiter character used to separate tokens.
 * @return The number of tokens found in the input string.
 *
 * @todo Change this with ft_strtkns and test it
 */

static size_t	count_tokens(char const *s, char c)
{
	size_t	counter;
	int		inside_token;

	counter = 0;
	inside_token = 0;
	while (*s)
	{
		if (*s != c && !inside_token)
		{
			inside_token = 1;
			++counter;
		}
		else if (*s == c)
			inside_token = 0;
		++s;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	size_t	c_count;
	char	**str_cont;

	if (!s)
		return (NULL);
	c_count = count_tokens(s, c);
	str_cont = malloc(sizeof(char *) * (c_count + 1));
	if (!str_cont)
		return (NULL);
	if (!set_substrs(s, str_cont, c, c_count))
	{
		ft_matrix_free((void ***)&str_cont, 0);
		return (NULL);
	}
	str_cont[c_count] = NULL;
	return (str_cont);
}
