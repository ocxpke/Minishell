/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_enviroment_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:44 by pablo             #+#    #+#             */
/*   Updated: 2025/11/09 16:02:55 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_value_env_node(t_envp *shell_env, const char *key, char *new_key)
{
	t_linked_env	*search_normal_list;
	t_linked_env	*search_ordered_list;

	if (!key || !shell_env || !shell_env->envp || !shell_env->ordered_envp)
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

int	modify_exit_status_value(t_envp *shell_envp, int new_exit_status)
{
	char	*new_val;

	new_exit_status %= 256;
	new_val = ft_itoa(new_exit_status);
	if (!new_val)
		return (perror("Malloc error\n"), 0);
	modify_value_env_node(shell_envp, "FT_EXIT_ENV", new_val);
	free(new_val);
	return (1);
}
