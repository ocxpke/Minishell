/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_collapse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:01:32 by pablo             #+#    #+#             */
/*   Updated: 2025/11/04 18:35:38 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * Frees a dynamically allocated array of string matrices.
 *
 * This function iterates through an array of string matrices (extracted) and
 * frees each individual matrix using ft_matrix_free. After freeing all
 * matrices, it frees the top-level array itself.
 *
 * @param extracted A pointer to an array of string matrices to be freed.
 * @param extracted_size The number of matrices in the extracted array.
 */
static void	free_extracted(char ***extracted, size_t extracted_size)
{
	size_t	k;

	k = 0;
	while (k < extracted_size)
	{
		if (extracted[k])
			ft_matrix_free((void ***)&extracted[k], 0);
		k++;
	}
	ft_matrix_free((void ***)&extracted, extracted_size);
}

/**
 * @brief Flattens a 2D array of strings into a single array.
 *
 * Allocates a new array of strings and copies all strings from the arrays
 * in extracted into this new array, preserving their order. The resulting
 * array is NULL-terminated. Frees the memory used by extracted after
 * collapsing.
 *
 * @param extracted A pointer to an array of string arrays to be collapsed.
 * @param extracted_size The number of arrays in extracted.
 * @param final_size The total number of strings expected in the collapsed
 *                   array.
 * @return The collapsed array on success, or NULL on allocation failure.
 */
static char	**collapse_loop(char ***extracted, size_t extracted_size,
		size_t final_size)
{
	char	**collapsed;
	size_t	i;
	size_t	j;
	size_t	k;

	collapsed = ft_calloc(final_size + 1, sizeof(char *));
	if (!collapsed)
		return (free_extracted(extracted, extracted_size), NULL);
	i = 0;
	k = 0;
	while (k < extracted_size)
	{
		j = 0;
		while (extracted[k][j])
		{
			collapsed[i++] = ft_strdup(extracted[k][j++]);
			if (!collapsed[i - 1])
				return (free_extracted(extracted, extracted_size),
					ft_matrix_free((void ***)collapsed, 0), NULL);
		}
		++k;
	}
	collapsed[i] = NULL;
	free_extracted(extracted, extracted_size);
	return (collapsed);
}

char	**collapse_extracted(char ***extracted)
{
	size_t	extracted_size;
	size_t	final_size;
	size_t	i;

	extracted_size = ft_matrix_len((void **)extracted);
	i = 0;
	final_size = 0;
	while (i < extracted_size)
	{
		final_size += ft_matrix_len((void **)extracted[i]);
		++i;
	}
	return (collapse_loop(extracted, extracted_size, final_size));
}
