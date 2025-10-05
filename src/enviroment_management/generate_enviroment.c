#include "minishell.h"

extern char	**environ;

//Arreglado y optimizado, añade o modifica al env PID
static int	add_exit_env(t_envp *enviroment)
{
	int		ret;
	char	*exit_env;
	char	**key_value;

	exit_env = "FT_EXIT_ENV=0";
	key_value = get_key_value(exit_env);
	ret = edit_env_lists(enviroment, key_value);
	return (free_splitted_string(key_value), ret);
}

//Arreglado y optimizado, añade o modifica al env PID
static int	add_pid_env(t_envp *enviroment)
{
	int		ret;
	char	*pid_from_file;
	char	*env_prepared;
	char	**key_value;

	pid_from_file = get_pid_from_file();
	if (!pid_from_file)
		return (0);
	env_prepared = get_pid_env(pid_from_file);
	if (!env_prepared)
		return (free(pid_from_file), 0);
	key_value = get_key_value(env_prepared);
	if (!key_value)
		return (free(pid_from_file), free(env_prepared), 0);
	ret = edit_env_lists(enviroment, key_value);
	free_splitted_string(key_value);
	return (free(pid_from_file), free(env_prepared), ret);
}

void	clone_environs(t_envp *enviroment)
{
	int		i;
	char	**key_value;

	i = 0;
	while (environ[i])
	{
		key_value = get_key_value(environ[i]);
		if (key_value)
		{
			check_if_shelllvl(key_value);
			edit_env_lists(enviroment, key_value);
			free_splitted_string(key_value);
		}
		i++;
	}
	enviroment->len_env = i + add_pid_env(enviroment) + add_exit_env(enviroment);
}

//Nos genera las variables de entorno que nos llevaremos a execve
int	generate_exec_envp(t_envp *shell_envi)
{
	t_linked_env	*aux;
	char			*env;
	int				i;

	shell_envi->envp_exec = (char **)ft_calloc(shell_envi->len_env + 1,
			sizeof(char *));
	if (!shell_envi->envp_exec)
		return (perror("Error creating envp_exec\n"), 0);
	aux = shell_envi->envp;
	i = 0;
	while (aux && (i <= shell_envi->len_env))
	{
		env = ft_calloc(1, ft_strlen(aux->key) + 1 + ft_strlen(aux->value) + 1);
		if (!env)
			return (perror("BOOM in exec_envp"), 1);
		ft_strlcat(env, aux->key, ft_strlen(aux->key) + 1
			+ ft_strlen(aux->value) + 1);
		ft_strlcat(env, "=", ft_strlen(aux->key) + 1 + ft_strlen(aux->value)
			+ 1);
		if (aux->value)
			ft_strlcat(env, aux->value, ft_strlen(aux->key) + 1
				+ ft_strlen(aux->value) + 1);
		shell_envi->envp_exec[i] = env;
		i++;
		aux = aux->next;
	}
	return (1);
}

//Libera la lista enlazada de forma ordenada
void	free_env_linked_list(t_linked_env **linked_env)
{
	t_linked_env	*aux;
	t_linked_env	*to_free;

	aux = *linked_env;
	while (aux)
	{
		to_free = aux;
		aux = aux->next;
		free(to_free->key);
		free(to_free->value);
		free(to_free);
	}
	*linked_env = NULL;
}
