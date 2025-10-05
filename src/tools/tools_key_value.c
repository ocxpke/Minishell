#include "minishell.h"

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
