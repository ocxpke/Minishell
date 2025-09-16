/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:39:27 by pablo             #+#    #+#             */
/*   Updated: 2025/09/16 18:27:01 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Advances pointer past env var name.
 *
 * Increments pointer to skip initial char (e.g., '$'), then
 * continues while current char is alphanumeric or '?'
 * (for special vars like $?).
 *
 * @param env_start: Pointer to start of env var (usually at '$').
 *
 * @returns Pointer to char after env var name.
 */
static char	*get_env_end(char *env_start)
{
	++env_start;
	while (ft_isprint(*env_start) && !ft_isspace(*env_start))
		++env_start;
	return (env_start);
}

/**
 * @brief Expands an environment variable in a string.
 *
 * Locates an env var at `env_start` in `*current_string`, gets its value
 * from `linked_env`, and replaces it in the string. Special handling for
 * `$?` (mapped to "FT_STATUS"). If not found, replaces with empty string.
 * If just `$`, preserves it. Result is trimmed of double quotes and
 * search position pointer is updated.
 *
 * @param env_start Pointer to start of env var in the string.
 * @param current_string Pointer to the string being processed; updated.
 * @param next_search_pos Pointer to next env var search position; updated.
 * @param linked_env Linked list of env var names and values.
 *
 * @return Updated string with env var expanded.
 */
static char	*expand_env(char *env_start, char **current_string,
		char **next_search_pos, t_linked_env *linked_env)
{
	char	*env;
	char	*env_end;
	char	*env_value;
	char	*result;
	size_t	offset;

	env_end = get_env_end(env_start);
	env = ft_strndup(env_start + 1, env_end - env_start);
	offset = env_start - *current_string;
	if (env_end - 1 != env_start)
	{
		if (!ft_strncmp(env, "?", ft_strlen(env)))
			env_value = get_linked_env("FT_STATUS", linked_env);
		else
			env_value = get_linked_env(env, linked_env);
		if (!env_value)
			env_value = "";
	}
	else
		env_value = "$";
	result = ft_strinsert(*current_string, env_start, env_end, env_value);
	free(*current_string);
	free(env);
	*current_string = ft_strtrim(result, "\"");
	free(result);
	*next_search_pos = *current_string + offset + ft_strlen(env_value);
	return (*current_string);
}

/**
 * @brief Removes leading/trailing quotes from a string.
 *
 * Trims leading/trailing single (') or double (") quotes from the string
 * pointed to by `current_string`. Frees the original string and
 * replaces it with the trimmed version.
 *
 * @param current_string Pointer to the string pointer to clean quotes from.
 */
static void	clean_quote(char **current_string)
{
	char	*tmp;

	tmp = ft_strtrim(*current_string, "\"\'");
	free(*current_string);
	*current_string = tmp;
}


char	**parse_expand_env(char **splitted, t_linked_env *linked_env)
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
				clean_quote(&splitted[i]);
			while (env_start)
			{
				expand_env(env_start, &splitted[i], &next_search_pos,
					linked_env);
				env_start = ft_strchr(next_search_pos, '$');
			}
		}
		else
			clean_quote(&splitted[i]);
		++i;
	}
	return (splitted);
}
