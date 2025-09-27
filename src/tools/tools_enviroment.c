/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_enviroment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:03:07 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 21:10:22 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	clone_environs(t_envp *enviroment)
{
	int		i;
	char	**key_value;

	i = 0;
	while (environ[i])
	{
		//TODO: Si esto es NULL, hay que mover erro para arriba
		key_value = get_key_value(environ[i]);
		if (key_value)
		{
			check_if_shelllvl(key_value);
			add_normal_node(&(enviroment->envp), key_value);
			add_ordered_node(&(enviroment->ordered_envp), key_value);
			free_splitted_string(key_value);
		}
		i++;
	}
	enviroment->len_env = i + add_pid_env(enviroment);
}

void	free_splitted_string(char **splitted)
{
	int	i;

	i = 0;
	if (!splitted)
		return ;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

/**
 * @note la palabra 'key' tiene ciertas restricciones, las haremos?????
 */

char	**get_key_value(char *env)
{
	char	**ret;
	char	*key;
	char	*value;
	int		first_eq;

	if (!env || (env[0] == '='))
		return (NULL);
	ret = (char **)ft_calloc(3, sizeof(char *));
	if (!ret)
		return (perror("Error generating matrix key value\n"), NULL);
	if (!ft_strchr(env, '='))
		return (ret[0] = ft_strdup(env), ret[1] = NULL, ret);
	first_eq = ft_strchr(env, '=') - env;
	key = ft_substr(env, 0, first_eq);
	if (!key || !ft_strlen(key))
		return (free(key), free_splitted_string(ret), NULL);
	value = ft_strdup(&env[first_eq + 1]);
	ret[0] = key;
	ret[1] = value;
	return (ret);
}
