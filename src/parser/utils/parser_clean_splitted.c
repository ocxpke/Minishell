/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_splitted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:48:25 by pablo             #+#    #+#             */
/*   Updated: 2025/11/04 18:14:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Processes and adds a trimmed string to the result array.
 *
 * Trims whitespace from the input string and reallocates the result array
 * to accommodate the new string. Handles memory allocation failures by
 * cleaning up all allocated resources.
 *
 * @param splitted Original array of strings (freed on error).
 * @param tmp Current result array (may be reallocated).
 * @param str String to trim and add.
 * @param j Pointer to the current index in the result array.
 * @return Updated result array on success, or NULL on failure.
 */
static char	**process_and_add_trimmed(char **splitted, char **tmp, char *str,
		size_t *j)
{
	char	*trimmed;
	char	**new_tmp;

	trimmed = ft_strtrim(str, " ");
	if (!trimmed)
		return (ft_matrix_free((void ***)&tmp, 0),
			ft_matrix_free((void ***)&splitted, 0), NULL);
	new_tmp = (char **)ft_realloc(tmp, sizeof(char *) * (*j), sizeof(char *)
			* ((*j) + 1));
	if (!new_tmp)
		return (free(trimmed), ft_matrix_free((void ***)&tmp, 0),
			ft_matrix_free((void ***)&splitted, 0), NULL);
	new_tmp[(*j)++] = trimmed;
	return (new_tmp);
}

/**
 * @brief Builds a cleaned temporary array from the input split array.
 *
 * This function processes each element in the provided `splitted` array,
 * trims and potentially filters them (e.g., excluding empty strings), and
 * constructs a new dynamically allocated array containing the cleaned
 * elements. The new array is null-terminated.
 *
 * @param splitted A null-terminated array of strings to be processed.
 * @return A pointer to the newly allocated cleaned array, or NULL if
 *         memory allocation fails or an error occurs during processing.
 *         The caller is responsible for freeing the returned array.
 */
static char	**build_clean_tmp(char **splitted)
{
	size_t	ij[2];
	char	**tmp;
	char	**new_tmp;

	ij[0] = 0;
	ij[1] = 0;
	tmp = NULL;
	while (splitted[ij[0]])
	{
		tmp = process_and_add_trimmed(splitted, tmp, splitted[ij[0]++], &ij[1]);
		if (!tmp)
			return (NULL);
	}
	if (ij[1] != 0)
	{
		new_tmp = (char **)ft_realloc(tmp, sizeof(char *) * ij[1],
				sizeof(char *) * (ij[1] + 1));
		if (!new_tmp)
			return (ft_matrix_free((void ***)&tmp, 0), NULL);
		tmp = new_tmp;
	}
	tmp[ij[1]] = NULL;
	return (tmp);
}

char	**clean_splitted(char **splitted)
{
	char	**tmp;

	if (!splitted)
		return (NULL);
	tmp = build_clean_tmp(splitted);
	if (!tmp)
		return (NULL);
	ft_matrix_free((void ***)&splitted, 0);
	return (tmp);
}
