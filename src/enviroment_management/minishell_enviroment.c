#include "minishell.h"

//Generamos el string PID="XXXX" PARA DESPUES OBTENER EL PAR KEY_VALUE
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

//Nos devuelve la linea que contiene el PID
// del arvhivo /proc/self/status, hay que liberar dsps
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
	//TODO: Pablo arregla get_next_line, que hacemos con esto?
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
