/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:27:36 by pablo             #+#    #+#             */
/*   Updated: 2025/11/14 00:14:00 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of characters in a string, excluding those
 * inside quotes.
 *
 * This function iterates through the input string and counts characters
 * that are not enclosed within single or double quotes. It handles quote
 * toggling to skip quoted sections.
 *
 * @param str The input string to analyze.
 * @return The count of characters outside of quoted sections.
 */
static size_t	count_chars(char *str)
{
	size_t	count;
	char	in_quote;

	count = 0;
	in_quote = '\0';
	while (*str)
	{
		if (!in_quote && (*str == '\'' || *str == '\"'))
			in_quote = *str;
		else if (in_quote && *str == in_quote)
			in_quote = '\0';
		else
			++count;
		++str;
	}
	return (count);
}

/**
 * @brief Processes a string to remove quote delimiters while
 * preserving the content inside quotes.
 *
 * This function iterates through the input string, identifying
 * single ('') or double ("") quotes. It removes the quote
 * characters themselves but keeps the characters enclosed
 * within the quotes. The function handles nested quotes by
 * tracking the current quote state.
 *
 * @param str The input string to process, which may contain
 * quoted sections.
 * @param size The size of the input string (used for memory
 * allocation of the cleaned string).
 * @return A newly allocated string with quotes removed, or
 * NULL if memory allocation fails. The caller is responsible
 * for freeing the returned string.
 */
static char	*process_quotes(char *str, size_t size)
{
	char	*cleaned;
	char	in_quote;
	size_t	i;
	size_t	j;

	cleaned = ft_calloc(size + 1, sizeof(char));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = '\0';
	while (str[i])
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '\"'))
			in_quote = str[i];
		else if (in_quote && str[i] == in_quote)
			in_quote = '\0';
		else
			cleaned[j++] = str[i];
		++i;
	}
	return (cleaned);
}

void	clean_quote(char **str)
{
	char	*cleaned;
	size_t	size;

	if (!str || !*str)
		return ;
	size = count_chars(*str);
	if (size == ft_strlen(*str))
		return ;
	cleaned = process_quotes(*str, size);
	if (!cleaned)
		return ;
	free(*str);
	*str = cleaned;
}
