#include "minishell.h"

int generate_exec_envp(t_envp *shell_envi){
	t_linked_env *aux;
	char *env;
	int i;

	shell_envi->envp_exec = (char **)ft_calloc(shell_envi->len_env+1, sizeof(char *));
	if (!shell_envi->envp_exec)
		return (perror("Error creating envp_exec\n"), 0);
	aux = shell_envi->envp;
	i = 0;
	while (aux)
	{
		env = ft_calloc(1, ft_strlen(aux->key)+ ft_strlen(aux->value) + 1);
		if (!env)
			return(perror("BOOM in exec_envp"), 1);
		ft_strlcat(env, aux->key, ft_strlen(aux->key)+ ft_strlen(aux->value) + 1);
		if (aux->value)
			ft_strlcat(env, aux->value, ft_strlen(aux->key)+ ft_strlen(aux->value) + 1);
		shell_envi->envp_exec[i] = ft_strdup(env);
		i++;
		aux = aux->next;
	}
	return 1;
}

int add_normal_node(t_linked_env **envp, char **key_value)
{
	t_linked_env *new_node;
	t_linked_env *aux;

	new_node = (t_linked_env *)ft_calloc(1, sizeof(t_linked_env));
	if (!new_node)
		return(perror("Error creating new normal node\n"), 0);
	new_node->key = ft_strdup(key_value[0]);
	if(key_value[1])
		new_node->value = ft_strdup(key_value[1]);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (!(*envp))
		return(*envp = new_node, 1);
	aux = *envp;
	while(aux->next)
		aux = aux->next;
	aux->next = new_node;
	return (1);
}

//Revisar esto --> optimizar && partir seguro q tiene mas de 25 lineas
int add_ordered_node(t_linked_env **ordered_envp, char **key_value)
{
	t_linked_env *new_node;
	t_linked_env *aux;
	t_linked_env *prev;

	new_node = (t_linked_env *)ft_calloc(1, sizeof(t_linked_env));
	if (!new_node)
		return(perror("Error creating new ordered node\n"), 0);
	new_node->key = ft_strdup(key_value[0]);
	if(key_value[1])
		new_node->value = ft_strdup(key_value[1]);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (!(*ordered_envp))
		return(*ordered_envp = new_node, 1);
	//En cabeza
	if(ft_strncmp(new_node->key, (*ordered_envp)->key, ft_max_len_str(new_node->key, (*ordered_envp)->key)) < 0)
	{
		new_node->next = *ordered_envp;
		*ordered_envp = new_node;
		return 1;
	}
	//Caso generico
	aux = *ordered_envp;
	while(aux->next && (ft_strncmp(new_node->key, aux->key, ft_max_len_str(new_node->key, aux->key)) >= 0))
		aux = aux->next;
	if (!aux->next)
	{
		aux->next = new_node;
		return(1);
	}
	prev = *ordered_envp;
	while( prev->next && (prev->next!=aux))
		prev = prev->next;
	new_node->next = aux;
	prev->next = new_node;
	return 1;
}

void free_env_linked_list(t_linked_env **linked_env)
{
	t_linked_env *aux;
	t_linked_env *to_free;

	aux = *linked_env;
	while(aux){
		to_free = aux;
		aux = aux->next;
		free(to_free->key);
		free(to_free->value);
		free(to_free);
	}
	*linked_env = NULL;
}
