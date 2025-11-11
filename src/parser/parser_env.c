/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:39:27 by pablo             #+#    #+#             */
/*   Updated: 2025/11/11 17:59:27 by pabmart2         ###   ########.fr       */
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
 * @brief Expands an environment variable substring into its value.
 *
 * This function extracts the environment variable name from the substring
 * between `env_start` and `env_end`, looks up its value in the linked
 * environment list, and returns a duplicated string of that value. If the
 * variable is "$?", it retrieves the exit status. If the substring is just
 * "$", it returns "$". If the variable is not found, it returns an empty
 * string.
 *
 * @param env_start Pointer to the start of the environment variable
 * substring (after '$').
 * @param env_end Pointer to the end of the environment variable substring.
 * @param linked_env Pointer to the linked list of environment variables.
 * @return A newly allocated string containing the expanded value, or NULL
 * on failure.
 */
static char	*get_expanded_value(char *env_start, char *env_end,
		t_linked_env *linked_env)
{
	char	*env;
	char	*env_value;

	env = ft_strndup(env_start + 1, env_end - env_start - 1);
	if (!env)
		return (NULL);
	if (env_end - 1 != env_start)
	{
		if (!ft_strncmp(env, "?", ft_strlen(env)))
			env_value = ft_strdup(get_env_value("FT_EXIT_ENV", linked_env));
		else
			env_value = ft_strdup(get_env_value(env, linked_env));
		if (!env_value)
			env_value = ft_strdup("");
		if (!env_value)
			return (free(env), NULL);
	}
	else
	{
		env_value = ft_strdup("$");
		if (!env_value)
			return (free(env), NULL);
	}
	free(env);
	return (env_value);
}

/**
 * @brief Expands an environment variable in the current string and
 * updates the string accordingly.
 *
 * This function identifies the environment variable starting at
 * `env_start`, retrieves its value, inserts it into the
 * `current_string` by replacing the variable reference, trims
 * surrounding quotes, and updates the `next_search_pos` to point
 * after the inserted value.
 *
 * @param env_start Pointer to the start of the environment variable
 * (e.g., after '$').
 * @param current_string Pointer to the string being processed; will
 * be modified and reallocated.
 * @param next_search_pos Pointer to update with the position after
 * the expanded value.
 * @param linked_env Linked list of environment variables for lookup.
 *
 * @return The updated `current_string` on success, or NULL on failure
 * (e.g., memory allocation error).
 *
 * @note The function frees the original `current_string` and any
 * intermediate strings on success. On failure, it frees allocated
 * resources and returns NULL.
 */
static char	*expand_env(char *env_start, char **current_string,
		char **next_search_pos, t_linked_env *linked_env)
{
	char	*env_end;
	char	*env_value;
	char	*result;
	char	*trimmed;
	size_t	offset;

	env_end = get_env_end(env_start);
	env_value = get_expanded_value(env_start, env_end, linked_env);
	if (!env_value)
		return (NULL);
	offset = env_start - *current_string;
	result = ft_strinsert(*current_string, env_start, env_end, env_value);
	if (!result)
		return (free(env_value), NULL);
	trimmed = ft_strtrim(result, "\"");
	free(result);
	if (!trimmed)
		return (free(env_value), NULL);
	free(*current_string);
	*current_string = trimmed;
	*next_search_pos = *current_string + offset + ft_strlen(env_value);
	free(env_value);
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
				if (!expand_env(env_start, &splitted[i], &next_search_pos,
						linked_env))
					return (ft_matrix_free((void ***)&splitted, 0), NULL);
				env_start = ft_strchr(next_search_pos, '$');
			}
		}
		else
			clean_quote(&splitted[i]);
		++i;
	}
	return (splitted);
}
