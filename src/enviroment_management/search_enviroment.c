/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_enviroment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:55 by pablo             #+#    #+#             */
/*   Updated: 2025/11/09 16:03:01 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_enviroment_value(const char *key, t_linked_env *linked_env)
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
