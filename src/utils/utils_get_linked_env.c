/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_linked_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:04:51 by pabmart2          #+#    #+#             */
/*   Updated: 2025/09/11 21:13:43 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_linked_env(const char *key, t_linked_env *linked_env)
{
	size_t		len;

	if (!key || !linked_env)
		return (NULL);
	len = ft_strlen(key);
	while (linked_env)
	{
		if (ft_strlen(linked_env->key) == len &&
			ft_strncmp(linked_env->key, key, len) == 0)
			return (linked_env->value);
		linked_env = linked_env->next;
	}
	return (NULL);
}
