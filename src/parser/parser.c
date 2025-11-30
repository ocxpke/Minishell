/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:57:25 by pablo             #+#    #+#             */
/*   Updated: 2025/11/30 12:53:40 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	has_command_in_pipeline(t_token **tokens, size_t i)
{
	ssize_t	j;

	j = (ssize_t)i - 1;
	while (j >= 0)
	{
		if (tokens[j]->token_type == PIPE)
			return (0);
		if (tokens[j]->token_type == COMMAND_BUILT_IN
			|| tokens[j]->token_type == COMMAND_ROUTE
			|| tokens[j]->token_type == COMMAND_NOT_FOUND)
			return (1);
		j--;
	}
	return (0);
}

/**
 * Checks if the given null-terminated array of strings contains a NULL
 * pointer.
 *
 * This function iterates through the array until it encounters a NULL
 * pointer (indicating the end of the array). It checks each element for
 * NULL, but due to the loop condition, it will never find one and always
 * returns 0.
 *
 * @param array A null-terminated array of strings (char **) to inspect.
 * @return Always 0, as the implementation does not correctly detect NULL
 * elements.
 */
static int	has_null_in_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		if (!array[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Checks if the given token type is a redirection operator.
 *
 * This function checks if the provided token type corresponds to a redirection
 * operator, such as REDIRECT_IN_CHAR, REDIRECT_IN_CHAR_HEREDOC,
 * REDIRECT_OUT_CHAR, or REDIRECT_OUT_CHAR_APPEND. It does not include PIPE.
 *
 * @param type The token type to check.
 * @return 1 if the type is a redirection operator, 0 otherwise.
 */
static int	is_redirection(t_ttype type)
{
	return (type == REDIRECT_IN_CHAR || type == REDIRECT_IN_CHAR_HEREDOC
		|| type == REDIRECT_OUT_CHAR || type == REDIRECT_OUT_CHAR_APPEND);
}

/**
 * @brief Checks for consecutive operators in the token array.
 *
 * This function iterates through the provided token array and verifies
 * that no invalid consecutive operators are present. Specifically:
 * - No two PIPE operators in a row.
 * - No two redirection operators in a row.
 * If such cases are found, it frees the token array, writes an error message
 * to stderr, and returns NULL. Otherwise, it returns the original token array.
 *
 * @param tokens A pointer to an array of t_token pointers to be checked.
 * @return The original token array if no consecutive operators are found,
 *         or NULL if an error occurs.
 */
static t_token	**check_tokens(t_token **tokens)
{
	t_token	**tmp;
	size_t	i;

	tmp = tokens;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->token_type == PIPE
			|| is_redirection(tokens[i]->token_type))
		{
			if (tokens[i + 1] && (((tokens[i]->token_type == PIPE)
						&& (tokens[i + 1]->token_type == PIPE))
					|| (is_redirection(tokens[i]->token_type)
						&& is_redirection(tokens[i + 1]->token_type))))
			{
				free_tokens(&tmp);
				write(STDERR_FILENO,
					"Error parsing: Multiple operators together\n", 43);
				return (NULL);
			}
		}
		i++;
	}
	return (tmp);
}

t_token	**parse(char *command_line, t_linked_env *linked_env)
{
	char	**splitted;
	t_token	**tokens;

	if (!command_line || !ft_strlen(command_line))
		return (NULL);
	splitted = split_pipes(command_line);
	if (!splitted)
		return (NULL);
	splitted = split_args(splitted);
	if (!splitted)
		return (NULL);
	splitted = parse_expand_env(splitted, linked_env);
	if (!splitted)
		return (NULL);
	if (has_null_in_array(splitted))
		return (ft_free((void **)&splitted), NULL);
	tokens = tokenize(splitted, linked_env);
	ft_matrix_free((void ***)&splitted, 0);
	return (check_tokens(tokens));
}
