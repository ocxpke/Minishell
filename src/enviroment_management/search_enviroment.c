#include "minishell.h"

char	*get_enviroment_value(const char *key, t_linked_env *linked_env)
{
	if (!key || !linked_env)
		return (NULL);
	while (linked_env)
	{
		if (!ft_strncmp(linked_env->key, key, ft_max_len_str(key, linked_env->key)))
			return (linked_env->value);
		linked_env = linked_env->next;
	}
	return (NULL);
}

t_linked_env *get_enviroment_node(const char *key, t_linked_env *linked_env)
{
	if (!key || !linked_env)
		return (NULL);
	while (linked_env)
	{
		if (!ft_strncmp(linked_env->key, key, ft_max_len_str(key, linked_env->key)))
			return (linked_env);
		linked_env = linked_env->next;
	}
	return (NULL);
}
