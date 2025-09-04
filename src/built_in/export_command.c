#include "minishell.h"

static int if_exists_replace(t_linked_env *env_list, char **key_value, int *ret)
{
	if (!ft_strncmp(env_list->key, key_value[0], ft_max_len_str(env_list->key, key_value[0])))
	{
		free(env_list->value);
		if (key_value[1])
			env_list->value = ft_strdup(key_value[1]);
		else
			env_list->value = NULL;
		*ret = 1;
	}
	return 1;
}

static int find_and_replace_env(t_envp *shell_envi, char **key_value)
{
	t_linked_env *aux_normal;
	t_linked_env *aux_ordered;
	int ret;

	ret = 0;
	aux_normal = shell_envi->envp;
	aux_ordered = shell_envi->ordered_envp;
	while(aux_normal && aux_ordered)
	{
		if_exists_replace(aux_normal, key_value, &ret);
		if_exists_replace(aux_ordered, key_value, &ret);
		aux_normal = aux_normal->next;
		aux_ordered = aux_ordered->next;
	}
	return (ret);
}

void export_cmd(t_shell_data *shell_data, int*ret)
{
	char **key_value;
	int i = 1;

	*ret = 1;
	if (!shell_data->tokens[1])
		return (print_envi_list(shell_data->shell_envi.ordered_envp, 0));
	while(shell_data->tokens[i])
	{
		key_value = get_key_value(shell_data->tokens[i]->string);
		if (key_value && !find_and_replace_env(&(shell_data-> shell_envi), key_value))
		{
			add_normal_node(&shell_data->shell_envi.envp, key_value);
			add_ordered_node(&shell_data->shell_envi.ordered_envp, key_value);
			shell_data->shell_envi.len_env++;
		}
		free_splitted_string(key_value);
		i++;
	}
}
