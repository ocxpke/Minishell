/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extractm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:29 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/28 14:33:44 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory and copies a substring fragment from the given
 *        string.
 *
 * This function allocates enough memory to hold the substring of 's' starting
 * at index 'start' and ending at index 'end' (inclusive), copies the substring
 * into the newly allocated memory, and returns a pointer to it.
 *
 * @param s     The source string from which to extract the fragment.
 * @param start The starting index of the fragment in 's'.
 * @param end   The ending index (inclusive) of the fragment in 's'.
 * @return      A pointer to the newly allocated and copied fragment,
 *              or NULL if memory allocation fails.
 */
static char	*allocate_and_copy_fragment(const char *s, size_t start, size_t end)
{
	char	*fragment;

	fragment = ft_calloc(end - start + 1, sizeof(char));
	if (!fragment)
		return (NULL);
	ft_strlcpy(fragment, s + start, end - start + 1);
	return (fragment);
}

/**
 * @brief Advances the index past a substring until a separator is found.
 *
 * Iterates through the string `s` starting at index `i` until it finds the
 * `separator` character or reaches the end. If the separator is found, the
 * index is incremented to move past it.
 *
 * @param s The input string to search.
 * @param i The starting index within the string.
 * @param separator The character to search for as a separator.
 * @return The updated index after skipping characters and the separator.
 */
static size_t	handle_separator(const char *s, size_t i, char separator)
{
	while (s[i] && s[i] != separator)
		i++;
	if (s[i] == separator)
		i++;
	return (i);
}

/**
 * @brief Splits a string into fragments based on separator characters and
 *        stores them in an array.
 *
 * This function iterates through the input string s, splitting it into
 * fragments separated by any character found in separators. For each
 * fragment, it allocates memory and copies the fragment into the str_cont
 * array. If a separator is encountered, it uses handle_separator to
 * determine the next position. If memory allocation fails for any fragment,
 * the function returns NULL.
 *
 * @param s              The input string to be split.
 * @param str_cont       The array of strings where the resulting
 *                       fragments will be stored.
 * @param separators     A string containing all separator characters.
 * @param fragment_count The number of fragments to extract from the
 *                       input string.
 *
 * @return The array str_cont containing the extracted fragments on
 *         success, or NULL if memory allocation fails.
 */
static char	**set_substrs(char const *s, char **str_cont,
		char const *separators, size_t fragment_count)
{
	size_t	fragment_idx;
	size_t	start;
	size_t	i;

	fragment_idx = 0;
	i = 0;
	while (s[i] && fragment_idx < fragment_count)
	{
		start = i;
		if (ft_strchr(separators, s[i]))
		{
			i = handle_separator(s, i + 1, s[i]);
		}
		else
			while (s[i] && !ft_strchr(separators, s[i]))
				i++;
		str_cont[fragment_idx] = allocate_and_copy_fragment(s, start, i);
		if (!str_cont[fragment_idx])
			return (NULL);
		fragment_idx++;
	}
	return (str_cont);
}

/**
 * @brief Counts the number of fragments in a string alternating between
 * separator and non-separator sections.
 *
 * This function counts both the fragments contained between separator
 * characters and the fragments outside of them, maintaining the alternating
 * order. For example, with separators "'" in string "'hello' world 'foo'":
 * it would count: "'hello'", " world ", "'foo'" = 3 fragments.
 *
 * @param s The input string to be analyzed.
 * @param separators The string containing separator characters.
 * @return The number of fragments found in the input string.
 */
static size_t	count_fragments(char const *s, char const *separators)
{
	size_t	counter;
	char	current_sep;

	counter = 0;
	while (*s)
	{
		if (ft_strchr(separators, *s))
		{
			current_sep = *s++;
			while (*s && *s != current_sep)
				s++;
			if (*s == current_sep)
				s++;
			counter++;
		}
		else
		{
			while (*s && !ft_strchr(separators, *s))
				s++;
			counter++;
		}
	}
	return (counter);
}

char	**ft_extractm(char const *s, char const *separators)
{
	size_t	fragment_count;
	char	**str_cont;

	if (!s || !separators)
		return (NULL);
	fragment_count = count_fragments(s, separators);
	str_cont = malloc(sizeof(char *) * (fragment_count + 1));
	if (!str_cont)
		return (NULL);
	if (!set_substrs(s, str_cont, separators, fragment_count))
	{
		ft_matrix_free((void **)str_cont, 0);
		return (NULL);
	}
	str_cont[fragment_count] = NULL;
	return (str_cont);
}
