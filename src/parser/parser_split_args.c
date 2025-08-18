/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:51:04 by pablo             #+#    #+#             */
/*   Updated: 2025/07/30 16:14:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**split_args(char **array)
{
	size_t	size;
	size_t	i;
	char	***tmp;

	size = ft_matrix_len((void **)array);
	i = 0;
	tmp = malloc(sizeof(char **) * (size + 1));
	if (!tmp)
		return (NULL);
	while (i < size)
	{
		if (array[i][0] != '\'' && array[i][0] != '\"')
			tmp[i] = ft_split(array[i], ' ');
		else
		{
			tmp[i] = malloc(sizeof(char *) * 2);
			if (!tmp[i])
				return (NULL);
			tmp[i][0] = ft_strdup(array[i]);
			tmp[i][1] = NULL;
		}
		++i;
	}
	tmp[i] = NULL;
	return (ft_matrix_free((void **)array, 0), collapse_extracted(tmp));
}
