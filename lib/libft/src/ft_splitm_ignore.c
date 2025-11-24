/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm_ignore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:29 by pabmart2          #+#    #+#             */
/*   Updated: 2025/11/24 21:15:01 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Extracts a token from the string, respecting ignore
 * delimiters.
 *
 * This function advances the string pointer to extract the next
 * token delimited by 'c', while toggling an ignore state when
 * encountering characters in 'ignore' (e.g., quotes). The token
 * is allocated and copied from the start to the end position.
 *
 * @param s A pointer to a pointer to the input string, updated to
 * point after the token.
 * @param c A string containing all possible delimiter characters.
 * @param ignore A string of characters that toggle the ignore
 * state (e.g., for quotes).
 * @return A newly allocated null-terminated string containing the
 * token, or NULL if allocation fails.
 */
static char	*extract_token(const char **s, char const *c, char const *ignore)
{
	const char	*start;
	size_t		len;
	int			inside_ignore;
	char		*token;

	inside_ignore = 0;
	start = *s;
	while (**s && (inside_ignore || !ft_strchr(c, **s)))
	{
		if (ft_strchr(ignore, **s))
			inside_ignore = !inside_ignore;
		(*s)++;
	}
	len = *s - start;
	token = ft_calloc(len + 1, sizeof(char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	while (**s && ft_strchr(c, **s))
		(*s)++;
	return (token);
}

/**
 * @brief Allocates and populates an array of substrings from the input
 *        string, splitting by a delimiter while ignoring specified
 *        characters.
 *
 * This function creates an array of strings by extracting tokens from the
 * input string `s`, using `c` as the delimiter. It ignores characters
 * specified in the `ignore` string (e.g., quotes) during token extraction.
 * The number of tokens to extract is given by `token_count`. The resulting
 * array is null-terminated.
 *
 * @param s The input string to split.
 * @param c A string containing all possible delimiter characters.
 * @param token_count The number of tokens to extract.
 * @return A null-terminated array of strings (char **) on success, or NULL
 *         on failure. Failure can occur due to memory allocation errors or
 *         issues in token extraction.
 *
 * @note The function skips leading delimiters in `s` before starting
 *       extraction. It relies on `extract_token` to handle individual token
 *       extraction and `ft_matrix_free` for cleanup on errors.
 */
static char	**set_substrs(char const *s, char const *c, size_t token_count,
		char const *ignore)
{
	char	**str_cont;
	size_t	substr_count;

	str_cont = malloc(sizeof(char *) * (token_count + 1));
	if (!str_cont)
		return (NULL);
	substr_count = 0;
	while (*s && ft_strchr(c, *s))
		++s;
	while (substr_count < token_count)
	{
		str_cont[substr_count] = extract_token(&s, c, ignore);
		if (!str_cont[substr_count])
		{
			ft_matrix_free((void ***)&str_cont, 0);
			return (NULL);
		}
		++substr_count;
	}
	str_cont[token_count] = NULL;
	return (str_cont);
}

/**
 * @brief Counts the number of tokens in a string, separated by a delimiter,
 *        while ignoring sections enclosed by characters from an ignore set.
 *
 * This function iterates through the input string `s` and counts tokens
 * separated by the character `c`. However, it ignores any parts of the string
 * that are enclosed by characters specified in the `ignore` string. For
 * example, if `ignore` contains quotes, the function will treat quoted
 * sections as non-delimiting.
 *
 * @param s The input string to parse.
 * @param c A string containing all possible delimiter characters.
 * @param ignore A string containing characters that define ignore sections
 *               (e.g., quotes). If NULL, no ignoring is performed.
 * @return The number of tokens found in the string.
 */
static size_t	count_tokens(char const *s, char const *c, char const *ignore)
{
	size_t	counter;
	int		inside_token;
	int		inside_ignore;

	counter = 0;
	inside_token = 0;
	inside_ignore = 0;
	while (*s)
	{
		if (ignore && ft_strchr(ignore, *s))
		{
			if (!inside_ignore && !inside_token && ++counter)
				inside_token = 1;
			inside_ignore = !inside_ignore;
		}
		else if (!inside_ignore && !ft_strchr(c, *s) && !inside_token
			&& ++counter)
			inside_token = 1;
		else if (!inside_ignore && ft_strchr(c, *s))
			inside_token = 0;
		++s;
	}
	return (counter);
}

char	**ft_splitm_ignore(char const *s, char const *c, char const *ignored)
{
	size_t	c_count;

	if (!s)
		return (NULL);
	c_count = count_tokens(s, c, ignored);
	return (set_substrs(s, c, c_count, ignored));
}
