/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_enviroment_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:39:22 by pablo             #+#    #+#             */
/*   Updated: 2025/10/30 16:36:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	edit_env_lists(t_envp *shell_env, char **key_value)
{
	t_linked_env	*aux_node;

	aux_node = get_enviroment_node(key_value[0], shell_env->envp);
	if (aux_node)
	{
		aux_node->value = ft_strdup(key_value[1]);
		aux_node = get_enviroment_node(key_value[0], shell_env->ordered_envp);
		aux_node->value = ft_strdup(key_value[1]);
		return (0);
	}
	add_normal_node(&(shell_env->envp), key_value);
	add_ordered_node(&(shell_env->ordered_envp), key_value);
	return (1);
}

int	add_normal_node(t_linked_env **envp, char **key_value)
{
	t_linked_env	*new_node;
	t_linked_env	*aux;

	new_node = (t_linked_env *)ft_calloc(1, sizeof(t_linked_env));
	if (!new_node)
		return (perror("Error creating new normal node\n"), 0);
	new_node->key = ft_strdup(key_value[0]);
	if (key_value[1])
		new_node->value = ft_strdup(key_value[1]);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (!(*envp))
		return (*envp = new_node, 1);
	aux = *envp;
	while (aux->next)
		aux = aux->next;
	aux->next = new_node;
	return (1);
}

/**
 * @brief Creates a new environment node for the linked list.
 *
 * This function allocates memory for a new t_linked_env structure and
 * initializes its fields based on the provided key-value pair. The key
 * is always duplicated from key_value[0]. If key_value[1] is present,
 * the value is duplicated; otherwise, it is set to NULL. The next
 * pointer is initialized to NULL.
 *
 * @param key_value A null-terminated array of strings where key_value[0]
 *                  is the key and key_value[1] (if present) is the value.
 * @return A pointer to the newly created t_linked_env node on success,
 *         or NULL if memory allocation fails (with an error message
 *         printed to stderr).
 */
static t_linked_env	*create_env_node(char **key_value)
{
	t_linked_env	*new_node;

	new_node = (t_linked_env *)ft_calloc(1, sizeof(t_linked_env));
	if (!new_node)
		return (perror("Error creating new ordered node\n"), NULL);
	new_node->key = ft_strdup(key_value[0]);
	if (key_value[1])
		new_node->value = ft_strdup(key_value[1]);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Inserts a new node into the ordered environment linked list.
 *
 * This function inserts the provided new_node into the ordered linked list
 * pointed to by ordered_envp, maintaining alphabetical order based on the
 * key comparison using ft_strncmp. The list is ordered lexicographically.
 *
 * @param ordered_envp A pointer to the pointer of the head of the ordered
 *                     environment list. This allows modification of the head
 *                     if necessary.
 * @param new_node     The new node to be inserted into the list. It is assumed
 *                     that new_node is properly initialized with a key and
 *                     other necessary fields.
 *
 * @note The function assumes that the list is already ordered and that
 *       ft_strncmp and ft_max_len_str are correctly implemented for string
 *       comparison.
 */
static void	insert_node_ordered(t_linked_env **ordered_envp,
		t_linked_env *new_node)
{
	t_linked_env	*aux;
	t_linked_env	*prev;

	aux = *ordered_envp;
	while (aux->next && (ft_strncmp(new_node->key, aux->key,
				ft_max_len_str(new_node->key, aux->key)) >= 0))
		aux = aux->next;
	if (!aux->next)
	{
		aux->next = new_node;
		return ;
	}
	prev = *ordered_envp;
	while (prev->next && (prev->next != aux))
		prev = prev->next;
	new_node->next = aux;
	prev->next = new_node;
}

int	add_ordered_node(t_linked_env **ordered_envp, char **key_value)
{
	t_linked_env	*new_node;

	new_node = create_env_node(key_value);
	if (!new_node)
		return (0);
	if (!(*ordered_envp))
		return (*ordered_envp = new_node, 1);
	if (ft_strncmp(new_node->key, (*ordered_envp)->key,
			ft_max_len_str(new_node->key, (*ordered_envp)->key)) < 0)
	{
		new_node->next = *ordered_envp;
		*ordered_envp = new_node;
		return (1);
	}
	insert_node_ordered(ordered_envp, new_node);
	return (1);
}
