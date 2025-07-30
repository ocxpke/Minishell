/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:27:58 by pablo             #+#    #+#             */
/*   Updated: 2025/07/30 21:21:49 by pablo            ###   ########.fr       */
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
