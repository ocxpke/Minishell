/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_splitted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:48:25 by pablo             #+#    #+#             */
/*   Updated: 2025/07/30 19:20:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Cleans a splitted string array by trimming spaces and removing empty
 * strings.
 *
 * Iterates over the input array of strings (`splitted`), trims leading and
 * trailing spaces from each string, and adds non-empty trimmed strings to a
 * new array. Empty strings (after trimming) are freed and not included in the
 * result. The resulting array is dynamically resized as needed and is
 * NULL-terminated. The original `splitted` array is freed before returning.
 *
 * @param splitted The input array of strings to be cleaned. Must be
 * NULL-terminated.
 * @return A newly allocated NULL-terminated array of cleaned strings. Returns
 * NULL if no strings remain.
 */
char	**clean_splitted(char **splitted)
{
	char	**tmp;
	char	*trimmed;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = NULL;
	while (splitted[i])
	{
		trimmed = ft_strtrim(splitted[i], " ");
		tmp = (char **)ft_realloc(tmp, sizeof(char *) * j, sizeof(char *) * (j
					+ 1));
		tmp[j++] = trimmed;
		i++;
	}
	if (j != 0)
		tmp = (char **)ft_realloc(tmp, sizeof(char *) * j, sizeof(char *) * (j
					+ 1));
	return (tmp[j] = NULL, ft_matrix_free((void **)splitted, 0), tmp);
}
