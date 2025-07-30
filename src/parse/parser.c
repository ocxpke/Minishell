/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:57:25 by pablo             #+#    #+#             */
/*   Updated: 2025/07/30 21:20:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	**parse(char *command_line)
{
	char	**splitted;
	t_token	**tokens;

	splitted = split_pipes(command_line);
	splitted = split_quotes(splitted);
	splitted = split_args(splitted);
	splitted = parse_expand_env(splitted);
	tokens = tokenize(splitted);
	free(splitted);
	return (tokens);
}
