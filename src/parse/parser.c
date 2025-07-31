/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:57:25 by pablo             #+#    #+#             */
/*   Updated: 2025/07/31 16:07:08 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	**parse(char *command_line)
{
	char	**splitted;
	t_token	**tokens;

	//Peuqeño cambio dejalo o quitalo a tu gusto pablo
	if (!command_line || !ft_strlen(command_line))
		return (NULL);
	splitted = split_pipes(command_line);
	splitted = split_quotes(splitted);
	splitted = split_args(splitted);
	splitted = parse_expand_env(splitted);
	tokens = tokenize(splitted);
	free(splitted);
	return (tokens);
}
