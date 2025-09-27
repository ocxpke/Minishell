/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_linked_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:04:51 by pabmart2          #+#    #+#             */
/*   Updated: 2025/09/27 19:03:40 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_linked_env(const char *key, t_linked_env *linked_env)
{
	size_t	len;

	if (!key || !linked_env)
		return (NULL);
	len = ft_strlen(key);
	while (linked_env)
	{
		if (ft_strlen(linked_env->key) == len && ft_strncmp(linked_env->key,
				key, len) == 0)
			return (linked_env->value);
		linked_env = linked_env->next;
	}
	return (NULL);
}
