/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_enviroment_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:44 by pablo             #+#    #+#             */
/*   Updated: 2025/10/28 18:50:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_value_env_node(t_envp *shell_env, const char *key, char *new_key)
{
	t_linked_env	*search_normal_list;
	t_linked_env	*search_ordered_list;

	if (!new_key || !shell_env || !shell_env->envp || !shell_env->ordered_envp)
		return (0);
	search_normal_list = get_enviroment_node(key, shell_env->envp);
	search_ordered_list = get_enviroment_node(key, shell_env->ordered_envp);
	if (!search_normal_list || !search_ordered_list)
		return (0);
	free(search_normal_list->value);
	free(search_ordered_list->value);
	search_normal_list->value = ft_strdup(new_key);
	search_ordered_list->value = ft_strdup(new_key);
	return (1);
}
