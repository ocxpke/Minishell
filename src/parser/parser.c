/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:57:25 by pablo             #+#    #+#             */
/*   Updated: 2025/10/26 14:48:37 by pabmart2         ###   ########.fr       */
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
	tokens = tokenize(splitted);
	ft_free((void **)&splitted);
	return (tokens);
}
