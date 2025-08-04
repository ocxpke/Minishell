/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:27:58 by pablo             #+#    #+#             */
/*   Updated: 2025/08/01 13:38:03 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**split_pipes(char *command_line)
{
	char	**tmp;

	tmp = ft_splitkeep(command_line, '|');
	if (!tmp)
		return (NULL);
	return (tmp);
}
