/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:10:16 by pablo             #+#    #+#             */
/*   Updated: 2025/07/31 13:20:19 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"


//TODO: Comprobar si hay que controlar dquote
char	**split_quotes(char **array)
{
	size_t	size;
	size_t	i;
	char	***extracted;

	size = ft_matrix_len((void **)array);
	extracted = malloc(sizeof(char **) * (size + 1));
	if (!extracted)
		return (ft_matrix_free((void **)array, 0), NULL);
	i = 0;
	while (i < size)
	{
		extracted[i] = clean_splitted(ft_extractm(array[i], "\'\""));
		++i;
	}
	extracted[i] = NULL;
	ft_matrix_free((void **)array, 0);
	return (collapse_extracted(extracted));
}
