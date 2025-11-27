/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:39:27 by pablo             #+#    #+#             */
/*   Updated: 2025/11/27 20:19:17 by pabmart2         ###   ########.fr       */
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
 * @brief Expands an environment variable from a string segment.
 *
 * This function extracts the environment variable name from the given string
 * segment defined by `env_start` and `env_end`, looks up its value in the
 * provided linked environment list, and returns a duplicated string of the
 * expanded value. Special handling is provided for the exit status variable
 * ("?") and for standalone "$" characters.
 *
 * @param env_start Pointer to the start of the environment variable segment
 *                  (typically after the '$' character).
 * @param env_end Pointer to the end of the environment variable segment.
 * @param linked_env Pointer to the linked list of environment variables.
 * @return A newly allocated string containing the expanded value, or NULL
 *         if memory allocation fails. If the variable is not found, an empty
 *         string is returned. For standalone "$", returns "$".
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
 * @brief Expands an environment variable in the current string.
 *
 * This function identifies the environment variable starting at
 * `env_start`, retrieves its expanded value using the provided linked
 * environment list, and replaces the variable in the string pointed to
 * by `current_string`. It then updates the search position to continue
 * parsing after the expansion.
 *
 * @param env_start Pointer to the start of the environment variable in
 * the string.
 * @param current_string Double pointer to the string being processed;
 * updated with the new string.
 * @param search_pos Double pointer to the current search position;
 * updated after expansion.
 * @param linked_env Pointer to the linked list of environment variables.
 * @return Pointer to the updated string on success, or NULL on failure
 * (e.g., memory allocation error or invalid env var).
 */
static char	*expand_env(char *env_start, char **current_string,
		char **search_pos, t_linked_env *linked_env)
{
	char	*env_end;
	char	*env_value;
	char	*result;
	size_t	offset;

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
	*search_pos = *current_string + offset + ft_strlen(env_value);
	free(env_value);
	return (*current_string);
}

/**
 * @brief Checks if the start of an environment variable is between
 * single quotes in a string.
 *
 * This function iterates through the input string, tracking whether
 * the current position is inside single quotes and double quotes.
 * It determines if the specified environment variable start position
 * is located between single quotes that are NOT inside double quotes.
 * Single quotes inside double quotes don't prevent expansion.
 *
 * @param str The input string to analyze.
 * @param env_start A pointer to the start of the environment variable
 * within the string.
 * @return 1 if the environment variable start is between single quotes
 * (and not inside double quotes), 0 otherwise.
 */
static char	is_env_between_quotes(char *str, char *env_start)
{
	char	inside_single;
	char	inside_double;
	char	env_start_reached;

	inside_single = 0;
	inside_double = 0;
	env_start_reached = 0;
	while (*str)
	{
		if (!inside_single && !inside_double && *str == '\'')
			inside_single = 1;
		else if (!inside_double && inside_single && *str == '\'')
		{
			inside_single = 0;
			if (env_start_reached)
				return (1);
		}
		else if (!inside_single && *str == '"')
			inside_double = !inside_double;
		if (str == env_start && inside_single && !inside_double)
			env_start_reached = 1;
		++str;
	}
	return (0);
}

char	**parse_expand_env(char **splitted, t_linked_env *linked_env)
{
	size_t	i;
	char	*env_start;
	char	*search_pos;

	i = 0;
	while (splitted[i])
	{
		search_pos = splitted[i];
		env_start = ft_strchr(search_pos, '$');
		while (env_start)
		{
			if (is_env_between_quotes(splitted[i], env_start))
				search_pos = env_start + 1;
			else if (!expand_env(env_start, &splitted[i], &search_pos,
					linked_env))
				return (ft_matrix_free((void ***)&splitted, 0), NULL);
			env_start = ft_strchr(search_pos, '$');
		}
		clean_quote(&splitted[i++]);
	}
	return (splitted);
}
