/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitkeep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:29 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/30 22:18:15 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Saves a separator character as a substring in the provided array.
 *
 * This function allocates memory for a new substring containing only the
 * separator character `c`, stores it in `str_cont` at the position indicated
 * by `*substr_count`, and updates both `*substr_count` and `*s` to point to
 * the next positions. Returns 1 if memory allocation fails, otherwise 0.
 *
 * @param str_cont      Array of strings to store the separator substring.
 * @param substr_count  Pointer to the current count/index for substrings.
 * @param c             The separator character to save.
 * @param s             Pointer to the current position in the input string.
 * @return int          0 on success, 1 on memory allocation failure.
 */
static int	save_separator(char **str_cont, size_t *substr_count, char c,
		char const **s)
{
	str_cont[*substr_count] = ft_calloc(2, sizeof(char));
	if (!str_cont[*substr_count])
		return (1);
	str_cont[*substr_count][0] = c;
	str_cont[*substr_count][1] = '\0';
	++(*substr_count);
	++(*s);
	return (0);
}

/**
 * @brief Splits the input string into substrings separated by a delimiter.
 *
 * Splits the string `s` into substrings separated by the delimiter `c`,
 * storing them in `str_cont`. Processes up to `token_count` tokens.
 * Allocates memory for each substring and copies it. If a separator is
 * found, `save_separator` is called. Returns the array of substrings
 * on success, or NULL on allocation failure.
 *
 * @param s           The input string to split.
 * @param str_cont    Array to store pointers to substrings.
 * @param c           The delimiter character.
 * @param token_count Maximum number of tokens to process.
 * @return            Pointer to array of substrings, or NULL on failure.
 */
static char	**set_substrs(char const *s, char **str_cont, char c,
		size_t token_count)
{
	size_t	substr_count;
	size_t	subs_str_len;
	char	*next_t;

	substr_count = 0;
	while (substr_count < token_count && *s)
	{
		if (*s != c)
		{
			next_t = ft_strchr(s, c);
			subs_str_len = (next_t - s);
			if (!next_t)
				subs_str_len = (ft_strchr(s, '\0') - s);
			str_cont[substr_count] = ft_calloc(subs_str_len + 1, sizeof(char));
			if (!str_cont[substr_count])
				return (NULL);
			ft_strlcpy(str_cont[substr_count], s, subs_str_len + 1);
			s += subs_str_len;
			++substr_count;
		}
		else if (save_separator(str_cont, &substr_count, c, &s))
			return (NULL);
	}
	return (str_cont);
}

/**
 * @brief Counts the number of tokens in a string separated by a given
 *        delimiter.
 *
 * This function iterates through the input string `s` and counts the number of
 * tokens separated by the character `c`. A token is defined as a contiguous
 * sequence of characters that are not the delimiter `c`, and each occurrence
 * of the delimiter `c` is also counted as a separate token.
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
		{
			if (inside_token)
				inside_token = 0;
			++counter;
		}
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

char	**ft_splitkeep(char const *s, char c)
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
