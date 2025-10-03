/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_modify_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:03:27 by jose-ara          #+#    #+#             */
/*   Updated: 2025/10/03 16:45:40 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pid_env(char *pid)
{
	char	env[256];
	char	*substr;
	int		i;

	ft_bzero((void *)env, 256);
	ft_strlcat(env, "Pid=", 256);
	i = 0;
	while (pid[i] && !ft_isdigit(pid[i]))
		i++;
	substr = ft_substr(pid, i, ft_strlen(&pid[i]) - 1);
	if (!substr)
		return (0);
	ft_strlcat(env, substr, 256);
	free(substr);
	return (ft_strdup(env));
}

static char	*get_pid_from_file(void)
{
	int		fd;
	int		found;
	char	*env;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (NULL);
	found = 0;
	env = "a";
	while (env && !found)
	{
		env = ft_get_next_line(fd);
		if (env && !ft_strncmp(env, "Pid:", 4))
			found = 1;
		if (!found)
			free(env);
	}
	close(fd);
	if (!found)
		return (NULL);
	return (env);
}

/**
 * @note peazo mierda, funciona pero es muy guarro
 */
int	pid_exists(t_envp *enviroment, char *pid)
{
	t_linked_env	*aux;
	char			*substr;
	int				i;

	aux = enviroment->envp;
	if (!pid)
		return (0);
	i = 0;
	while (pid[i] && !ft_isdigit(pid[i]))
		i++;
	substr = ft_substr(pid, i, ft_strlen(&pid[i]) - 1);
	if (!substr)
		return (0);
	while (aux && (ft_strncmp("Pid", aux->key, 3) != 0))
		aux = aux->next;
	if (aux)
		aux->value = ft_strdup(substr);
	else
		return (0);
	aux = enviroment->ordered_envp;
	while (aux && ft_strncmp("Pid", aux->key, 3))
		aux = aux->next;
	if (aux)
		aux->value = ft_strdup(substr);
	free(substr);
	return (1);
}

int	add_pid_env(t_envp *enviroment)
{
	char	*pid_from_file;
	char	*env_prepared;
	char	**key_value;

	pid_from_file = get_pid_from_file();
	if (!pid_from_file)
		return (0);
	if (pid_exists(enviroment, pid_from_file))
		return (free(pid_from_file), 1);
	env_prepared = get_pid_env(pid_from_file);
	if (!env_prepared)
		return (free(pid_from_file), 0);
	key_value = get_key_value(env_prepared);
	if (!key_value)
		return (free(pid_from_file), free(env_prepared), 0);
	add_normal_node(&(enviroment->envp), key_value);
	add_ordered_node(&(enviroment->ordered_envp), key_value);
	free_splitted_string(key_value);
	return (free(pid_from_file), free(env_prepared), 1);
}


inline void	check_if_shelllvl(char **key_value)
{
	int	prev_num;

	if (!ft_strncmp(key_value[0], "SHLVL", 5))
	{
		prev_num = ft_atoi(key_value[1]);
		free(key_value[1]);
		prev_num++;
		key_value[1] = ft_itoa(prev_num);
	}
}
