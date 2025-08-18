/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:39:27 by pablo             #+#    #+#             */
/*   Updated: 2025/07/30 21:47:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Advances pointer past env var name.
 *
 * Increments pointer to skip initial char (e.g., '$'), then
 * continues while current char is alphanumeric.
 * Returns pointer to char after env var name.
 * @param env_start: Pointer to start of env var (usually at '$').
 */
static char	*get_env_end(char *env_start)
{
	++env_start;
	while (ft_isalnum(*env_start))
		++env_start;
	return (env_start);
}

/**
 * TODO: Expansión de #?. Esto debe ser una variable que necesito leer
 * de algún lado. Por ahora se queda comentado pero, en teoría, debería
 * funcionar así bien,
 * aunque habría que tener cuidado para el caso de las
 * comillas dobles, que sólo interpretan $?. O bien lo hago aqui, o lo
 * modularizo.
 *
 * if (ft_strlen(env) == 1 && env[0] == '?')
 * ft_strinsert(splitted[i], env_start, env_end, ft_itoa(status));
 * else
 */

/**
 * @brief Expands an environment variable in a string and updates splitted.
 *
 * Locates an environment variable in the input string, gets its value from
 * the environment, and replaces the variable reference with its value.
 * Trims any surrounding double quotes from the result and updates the
 * position for the next search.
 *
 * @param env_start Pointer to the start of the env variable in the string.
 * @param splitted Array of strings to update with the expanded value.
 * @param i Index in splitted for the string being processed.
 * @param next_search_pos Pointer to a char pointer updated to the position
 *        after the expanded env variable for subsequent searches.
 *
 * @return Pointer to the updated string in splitted after expansion.
 */
static char	*expand_env(char *env_start, char **splitted, size_t i,
		char **next_search_pos)
{
	char	*env;
	char	*env_end;
	char	*env_value;
	char	*result;
	size_t	offset;

	env_end = get_env_end(env_start);
	env = ft_strndup(env_start + 1, env_end - env_start);
	offset = env_start - splitted[i];
	if (env_end - 1 != env_start)
	{
		env_value = getenv(env);
		if (!env_value)
			env_value = "";
	}
	else
		env_value = "$";
	result = ft_strinsert(splitted[i], env_start, env_end, env_value);
	free(splitted[i]);
	free(env);
	splitted[i] = ft_strtrim(result, "\"");
	free(result);
	*next_search_pos = splitted[i] + offset + ft_strlen(env_value);
	return (splitted[i]);
}

/**
 * @brief Removes leading/trailing quotes from a string in an array.
 *
 * Trims leading/trailing single (') or double (") quotes from the string
 * at index `i` in the `splitted` array. Frees the original string and
 * replaces it with the trimmed version.
 *
 * @param splitted Array of strings to process.
 * @param i Index of the string in the array to clean quotes from.
 */
static void	clean_quote(char **splitted, size_t i)
{
	char	*tmp;

	tmp = ft_strtrim(splitted[i], "\"\'");
	free(splitted[i]);
	splitted[i] = tmp;
}

char	**parse_expand_env(char **splitted)
{
	size_t	i;
	char	*env_start;
	char	*next_search_pos;

	i = 0;
	while (splitted[i])
	{
		if (splitted[i][0] != '\'')
		{
			env_start = ft_strchr(splitted[i], '$');
			if (!env_start)
				clean_quote(splitted, i);
			while (env_start)
			{
				splitted[i] = expand_env(env_start, splitted, i,
						&next_search_pos);
				env_start = ft_strchr(next_search_pos, '$');
			}
		}
		else
			clean_quote(splitted, i);
		++i;
	}
	return (splitted);
}
