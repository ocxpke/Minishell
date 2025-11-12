/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:36 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/12 23:04:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Searches for and removes an environment variable from the linked
 * list by key.
 *
 * This function iterates through the provided linked list of environment
 * variables to find a node matching the given key. If found, it removes the
 * node from the list and frees the associated memory (key, value, and node
 * itself). If the node is the head of the list, it updates the list head
 * accordingly.
 *
 * @param env_list A pointer to the pointer of the head of the linked list of
 * environment variables.
 * @param key The key string to search for in the environment list.
 * @return 1 if the key was found and removed, 0 otherwise.
 *
 * @note The function assumes that the linked list nodes are of type
 * t_linked_env, which contains key, value, and next pointers. It uses
 * ft_strncmp for comparison and ft_max_len_str to determine the comparison
 * length.
 */
static int	search_in_env_list(t_linked_env **env_list, char *key)
{
	t_linked_env	*aux;
	t_linked_env	*prev_aux;
	int				loop;

	loop = 1;
	aux = *env_list;
	while (aux && loop)
	{
		if (!ft_strncmp(aux->key, key, ft_max_len_str(aux->key, key)))
			loop = 0;
		else
		{
			prev_aux = aux;
			aux = aux->next;
		}
	}
	if (!aux)
		return (0);
	if (!prev_aux)
		*env_list = aux->next;
	else
		prev_aux->next = aux->next;
	return (free(aux->key), free(aux->value), free(aux), 1);
}

void	unset_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret)
{
	int	i;

	i = 1;
	while (cinfo->cmd_and_args[i])
	{
		if (search_in_env_list(&(shell_data->shell_envi.envp),
				cinfo->cmd_and_args[i])
			&& search_in_env_list(&(shell_data->shell_envi.ordered_envp),
				cinfo->cmd_and_args[i]))
			shell_data->shell_envi.len_env--;
		i++;
	}
	*ret = 0;
}
