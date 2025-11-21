/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:51:04 by pablo             #+#    #+#             */
/*   Updated: 2025/11/21 18:34:30 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Cleans up a temporary array of string matrices.
 *
 * This function iterates through the provided array of string matrices (`tmp`),
 * freeing each individual matrix using `ft_matrix_free`, and then frees the
 * outer array itself. It assumes that the array is NULL-terminated.
 *
 * @param tmp A pointer to an array of string matrices (char ***) to be cleaned.
 *            The array must be NULL-terminated.
 */
static void	clean_tmp(char ***tmp)
{
	size_t	i;

	i = 0;
	while (tmp[i])
	{
		ft_matrix_free((void ***)&tmp[i], 0);
		i++;
	}
	free(tmp);
}

/**
 * @brief Allocates memory for a temporary array of string arrays.
 *
 * This function allocates memory for an array of pointers to strings
 * (char **), with space for 'size + 1' elements. The extra element is
 * typically used for a NULL terminator in array-based data structures.
 *
 * @param size The number of elements to allocate (excluding the NULL
 *             terminator).
 * @return A pointer to the allocated array on success, or NULL on memory
 *         allocation failure.
 */
static char	***allocate_tmp(size_t size)
{
	char	***tmp;

	tmp = ft_calloc(size + 1, sizeof(char **));
	if (!tmp)
		return (NULL);
	return (tmp);
}

/**
 * @brief Processes a single argument by splitting it considering quotes.
 *
 * @param arg The argument string to process.
 * @param tmp A pointer to an array of string arrays where the processed
 * argument(s) will be stored.
 * @param i The index in the tmp array where the result should be placed.
 *
 * @return 1 on success, 0 on memory allocation failure.
 */
static int	process_arg(char *arg, char ***tmp, size_t i)
{
	tmp[i] = ft_splitm_ignore(arg, "\t \n", "\"'");
	if (!tmp[i])
		return (0);
	return (1);
}

char	**split_args(char **array)
{
	size_t	size;
	size_t	i;
	char	***tmp;

	size = ft_matrix_len((void **)array);
	tmp = allocate_tmp(size);
	if (!tmp)
		return (ft_matrix_free((void ***)&array, 0), NULL);
	i = 0;
	while (i < size)
	{
		if (!process_arg(array[i], tmp, i))
		{
			clean_tmp(tmp);
			return (ft_matrix_free((void ***)&array, 0), NULL);
		}
		i++;
	}
	tmp[i] = NULL;
	return (ft_matrix_free((void ***)&array, 0), collapse_extracted(tmp));
}
