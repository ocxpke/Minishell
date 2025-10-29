/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enviroment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:25:03 by pablo             #+#    #+#             */
/*   Updated: 2025/10/29 11:04:35 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pid_env(char *pid)
{
	char	env[256];
	char	*substr;
	int		i;

	ft_bzero((void *)env, 256);
	ft_strlcat(env, "PID=", 256);
	i = 0;
	while (pid[i] && !ft_isdigit(pid[i]))
		i++;
	substr = ft_substr(pid, i, ft_strlen(&pid[i]) - 1);
	if (!substr)
		return (0);
	ft_strlcat(env, substr, 256);
	free(substr);
	env[255] = 0;
	return (ft_strdup(env));
}

char	*get_pid_from_file(void)
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
	ft_get_next_line(-1);
	close(fd);
	if (!found)
		return (NULL);
	return (env);
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
