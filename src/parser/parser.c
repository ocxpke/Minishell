/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:57:25 by pablo             #+#    #+#             */
/*   Updated: 2025/11/20 18:59:42 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	has_command_in_pipeline(t_token **tokens, size_t i)
{
	ssize_t	j;

	j = (ssize_t)i - 1;
	while (j >= 0)
	{
		if (tokens[j]->token_type == PIPE)
			return (0);
		if (tokens[j]->token_type == COMMAND_BUILT_IN
			|| tokens[j]->token_type == COMMAND_ROUTE
			|| tokens[j]->token_type == COMMAND_NOT_FOUND)
			return (1);
		j--;
	}
	return (0);
}

/**
 * Checks if the given null-terminated array of strings contains a NULL
 * pointer.
 *
 * This function iterates through the array until it encounters a NULL
 * pointer (indicating the end of the array). It checks each element for
 * NULL, but due to the loop condition, it will never find one and always
 * returns 0.
 *
 * @param array A null-terminated array of strings (char **) to inspect.
 * @return Always 0, as the implementation does not correctly detect NULL
 * elements.
 */
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
