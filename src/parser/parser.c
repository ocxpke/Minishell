/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:57:25 by pablo             #+#    #+#             */
/*   Updated: 2025/11/04 18:46:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	has_null_in_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		if (!array[i])
			return (1);
		i++;
	}
	return (0);
}

t_token	**parse(char *command_line, t_linked_env *linked_env)
{
	char	**splitted;
	t_token	**tokens;

	if (!command_line || !ft_strlen(command_line))
		return (NULL);
	splitted = split_pipes(command_line);
	if (!splitted)
		return (NULL);
	splitted = split_quotes(splitted);
	if (!splitted)
		return (NULL);
	splitted = split_args(splitted);
	if (!splitted)
		return (NULL);
	splitted = parse_expand_env(splitted, linked_env);
	if (!splitted)
		return (NULL);
	if (has_null_in_array(splitted))
		return (ft_free((void **)&splitted), NULL);
	tokens = tokenize(splitted, linked_env);
	ft_matrix_free((void ***)&splitted, 0);
	return (tokens);
}
