/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:56:12 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:22:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is present in a given set of characters.
 *
 * This function iterates through the provided set of characters to determine
 * if the specified character is present within the set.
 *
 * @param set A pointer to a null-terminated string representing the set of
 * characters.
 * @param c The character to check for presence in the set.
 * @return int Returns 1 if the character is found in the set, otherwise
 * returns 0.
 */
static int	checkset(char const *set, char const c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		++set;
	}
	return (0);
}

/**
 * @brief Copies a substring from the given string `s1` into the `trimmed`
 * string.
 *
 * This function copies characters from the `s1` string starting at the `start`
 * index and ending at the `end` index into the `trimmed` string. The copied
 * substring is null-terminated.
 *
 * @param s1 The original string from which the substring is copied.
 * @param trimmed The destination string where the trimmed substring will be
 * stored.
 * @param start The starting index of the substring in the original string `s1`.
 * @param end The ending index of the substring in the original string `s1`.
 * @return A pointer to the `trimmed` string containing the copied substring.
 */
static char	*set_trim(char const *s1, char *trimmed, int start, int end)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (s1[i] && i <= end)
		trimmed[j++] = s1[i++];
	trimmed[j] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		start;
	int		end;
	int		len;

	len = ft_strlen(s1);
	start = 0;
	while (checkset(set, s1[start]))
		++start;
	end = len - 1;
	if (start == len)
		return (ft_strdup(""));
	while (checkset(set, s1[end]))
		--end;
	len = end - start + 2;
	trimmed = malloc(len * sizeof(char));
	if (!trimmed)
		return (NULL);
	trimmed[len - 1] = '\0';
	return (set_trim(s1, trimmed, start, end));
}
