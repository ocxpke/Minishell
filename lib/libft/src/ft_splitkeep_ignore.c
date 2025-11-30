/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitkeep_ignore.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:00:00 by pabmart2          #+#    #+#             */
/*   Updated: 2025/11/30 12:26:18 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Extracts a token from the string respecting ignore characters.
 *
 * @param s The current position in the input string.
 * @param c The delimiter character.
 * @param ignore String of characters that toggle ignore state.
 * @return The length of the extracted token.
 */
static size_t	get_token_len(char const *str, char delim, char const *ignore)
{
	size_t	length;
	char	quote_char;

	length = 0;
	quote_char = 0;
	while (str[length] && (quote_char || str[length] != delim))
	{
		if (ft_strchr(ignore, str[length]))
		{
			if (!quote_char)
				quote_char = str[length];
			else if (quote_char == str[length])
				quote_char = 0;
		}
		length++;
	}
	return (length);
}

/**
 * @brief Saves a substring in the array (token or separator).
 *
 * @param str_cont Array to store pointers to substrings.
 * @param idx Pointer to current index in the array.
 * @param s The substring to save.
 * @param len Length of the substring to save (0 means save separator).
 * @return 0 on success, 1 on memory allocation failure.
 */
static int	save_substr(char **result, size_t *index, char const *str,
		size_t length)
{
	if (length == 0)
	{
		result[*index] = ft_calloc(2, sizeof(char));
		if (!result[*index])
			return (1);
		result[*index][0] = *str;
	}
	else
	{
		result[*index] = ft_calloc(length + 1, sizeof(char));
		if (!result[*index])
			return (1);
		ft_strlcpy(result[*index], str, length + 1);
	}
	(*index)++;
	return (0);
}

/**
 * @brief Processes tokens and fills the substring array.
 *
 * @param s The input string to split.
 * @param str_cont Array to store pointers to substrings.
 * @param c The delimiter character.
 * @param ignore String of characters that toggle ignore state.
 * @return Pointer to array of substrings, or NULL on failure.
 */
static char	**process_tokens(char const *str, char **result, char delim,
		char const *ignore)
{
	size_t	index;
	size_t	token_len;
	char	quote_char;

	index = 0;
	quote_char = 0;
	while (*str)
	{
		if (ft_strchr(ignore, *str) && (!quote_char || quote_char == *str))
			quote_char = (quote_char == *str) * 0 + (!quote_char) * (*str);
		if (!quote_char && *str == delim)
		{
			if (save_substr(result, &index, str++, 0))
				return (NULL);
		}
		else
		{
			token_len = get_token_len(str, delim, ignore);
			if (token_len > 0 && save_substr(result, &index, str, token_len))
				return (NULL);
			str += token_len;
		}
	}
	return (result);
}

/**
 * @brief Counts the number of tokens in a string separated by a given
 *        delimiter, while respecting ignore characters.
 *
 * This function iterates through the input string `s` and counts the number of
 * tokens separated by the character `c`. A token is defined as a contiguous
 * sequence of characters that are not the delimiter `c` (unless inside ignored
 * sections), and each occurrence of the delimiter `c` outside of ignored
 * sections is also counted as a separate token. Characters in `ignore` toggle
 * the ignore state (typically quotes).
 *
 * @param s The input string to be tokenized.
 * @param c The delimiter character used to separate tokens.
 * @param ignore String of characters that toggle ignore state (e.g., quotes).
 * @return The number of tokens found in the input string.
 */
static size_t	count_tokens(char const *str, char delim, char const *ignore)
{
	size_t	token_count;
	int		inside_token;
	char	quote_char;

	token_count = 0;
	inside_token = 0;
	quote_char = 0;
	while (*str)
	{
		if (ft_strchr(ignore, *str))
		{
			if (!quote_char)
				quote_char = *str;
			else if (quote_char == *str)
				quote_char = 0;
		}
		if (!quote_char && *str != delim && !inside_token && ++inside_token)
			++token_count;
		else if (!quote_char && *str == delim && ++token_count)
			inside_token = 0;
		++str;
	}
	return (token_count);
}

char	**ft_splitkeep_ignore(char const *str, char delim, char const *ignore)
{
	size_t	token_count;
	char	**result;

	if (!str)
		return (NULL);
	if (!ignore)
		ignore = "\"'";
	token_count = count_tokens(str, delim, ignore);
	if (token_count == 0)
		return (NULL);
	result = malloc(sizeof(char *) * (token_count + 1));
	if (!result)
		return (NULL);
	if (!process_tokens(str, result, delim, ignore))
	{
		ft_matrix_free((void ***)&result, 0);
		return (NULL);
	}
	result[token_count] = NULL;
	return (result);
}
