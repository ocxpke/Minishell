/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:29 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/29 16:36:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Splits a string into substrings based on a delimiter.
 *
 * This function takes an input string `s` and splits it into substrings
 * based on the delimiter character `c`. The resulting substrings are stored
 * in the array `str_cont`, which should have enough space to hold `token_count`
 * substrings. The function returns the array `str_cont` on success, or NULL
 * if memory allocation fails.
 *
 * @param s The input string to be split.
 * @param c The delimiter character.
 * @param token_count The number of substrings to be created.
 * @return The array of substrings on success, or NULL on failure.
 */
static char	**set_substrs(char const *s, char **str_cont, char c,
		size_t token_count)
{
	size_t	substr_count;
	size_t	subs_str_len;
	char	*next_t;

	substr_count = 0;
	while (*s == c)
		++s;
	while (substr_count < token_count)
	{
		if (*s && *s != c)
		{
			next_t = ft_strchr(s, c);
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
 * @brief Counts the number of tokens in a string separated by a given delimiter.
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

char	**ft_split(char const *s, char c)
{
	size_t	c_count;
	char	**str_cont;

	c_count = count_tokens(s, c);
	str_cont = malloc(sizeof(char *) * (c_count + 1));
	if (!str_cont)
		return (NULL);
	if (!set_substrs(s, str_cont, c, c_count))
	{
		ft_freemtx((void **)str_cont);
		return (NULL);
	}
	str_cont[c_count] = NULL;
	return (str_cont);
}
