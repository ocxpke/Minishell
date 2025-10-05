#include "minishell.h"

//return -> 0 modified, return -> added
int edit_env_lists(t_envp *shell_env, char **key_value)
{
	t_linked_env *aux_node;

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

// Revisar esto --> optimizar && partir seguro q tiene mas de 25 lineas
int	add_ordered_node(t_linked_env **ordered_envp, char **key_value)
{
	t_linked_env	*new_node;
	t_linked_env	*aux;
	t_linked_env	*prev;

	new_node = (t_linked_env *)ft_calloc(1, sizeof(t_linked_env));
	if (!new_node)
		return (perror("Error creating new ordered node\n"), 0);
	new_node->key = ft_strdup(key_value[0]);
	if (key_value[1])
		new_node->value = ft_strdup(key_value[1]);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (!(*ordered_envp))
		return (*ordered_envp = new_node, 1);
	// En cabeza
	if (ft_strncmp(new_node->key, (*ordered_envp)->key,
			ft_max_len_str(new_node->key, (*ordered_envp)->key)) < 0)
	{
		new_node->next = *ordered_envp;
		*ordered_envp = new_node;
		return (1);
	}
	// Caso generico
	aux = *ordered_envp;
	while (aux->next && (ft_strncmp(new_node->key, aux->key,
				ft_max_len_str(new_node->key, aux->key)) >= 0))
		aux = aux->next;
	if (!aux->next)
	{
		aux->next = new_node;
		return (1);
	}
	prev = *ordered_envp;
	while (prev->next && (prev->next != aux))
		prev = prev->next;
	new_node->next = aux;
	prev->next = new_node;
	return (1);
}
