/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_enviroment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:55 by pablo             #+#    #+#             */
/*   Updated: 2025/11/11 17:59:15 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *key, t_linked_env *linked_env)
{
	if (!key || !linked_env)
		return (NULL);
	while (linked_env)
	{
		if (!ft_strncmp(linked_env->key, key, ft_max_len_str(key,
					linked_env->key)))
			return (linked_env->value);
		linked_env = linked_env->next;
	}
	return (NULL);
}

t_linked_env	*get_enviroment_node(const char *key, t_linked_env *linked_env)
{
	if (!key || !linked_env)
		return (NULL);
	while (linked_env)
	{
		if (!ft_strncmp(linked_env->key, key, ft_max_len_str(key,
					linked_env->key)))
			return (linked_env);
		linked_env = linked_env->next;
	}
	return (NULL);
}
