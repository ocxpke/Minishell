/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:39:27 by pablo             #+#    #+#             */
/*   Updated: 2025/11/21 20:00:30 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Advances pointer past env var name.
 *
 * Increments pointer to skip initial char (e.g., '$'), then
 * continues while current char is alphanumeric, underscore, or '?'
 * (for special vars like $?).
 *
 * @param env_start: Pointer to start of env var (usually at '$').
 *
 * @returns Pointer to char after env var name.
 */
static char	*get_env_end(char *env_start)
{
	++env_start;
	if (*env_start == '?')
		return (env_start + 1);
	while (ft_isalnum(*env_start) || *env_start == '_')
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

	env = ft_strndup(env_start + 1, env_end - env_start);
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
	size_t	offset;

	// char	*trimmed;
	env_end = get_env_end(env_start);
	env_value = get_expanded_value(env_start, env_end, linked_env);
	if (!env_value)
		return (NULL);
	offset = env_start - *current_string;
	result = ft_strinsert(*current_string, env_start, env_end, env_value);
	if (!result)
		return (free(env_value), NULL);
	free(*current_string);
	*current_string = result;
	*next_search_pos = *current_string + offset + ft_strlen(env_value);
	free(env_value);
	return (*current_string);
}

static char	is_env_between_quotes(char *str, char *env_start)
{
	char	inside_quote;
	char	env_start_reached;

	inside_quote = 0;
	env_start_reached = 0;
	while (*str)
	{
		if (!inside_quote && *str == '\'')
			inside_quote = 1;
		else if (inside_quote && *str == '\'')
		{
			inside_quote = 0;
			if (env_start_reached)
				return (1);
		}
		if (str == env_start && inside_quote)
			env_start_reached = 1;
		++str;
	}
	return (0);
}

char	**parse_expand_env(char **splitted, t_linked_env *linked_env)
{
	size_t	i;
	char	*env_start;
	char	*next_search_pos;
	char	*search_pos;

	i = 0;
	while (splitted[i])
	{
		search_pos = splitted[i];
		while ((env_start = ft_strchr(search_pos, '$')))
		{
			if (is_env_between_quotes(splitted[i], env_start))
				search_pos = env_start + 1;
			else
			{
				if (!expand_env(env_start, &splitted[i], &next_search_pos,
						linked_env))
					return (ft_matrix_free((void ***)&splitted, 0), NULL);
				search_pos = next_search_pos;
			}
		}
		clean_quote(&splitted[i++]);
	}
	return (splitted);
}
