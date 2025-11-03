/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:21:57 by pablo             #+#    #+#             */
/*   Updated: 2025/10/28 18:10:32 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Assigns the token type to tokens[i] based on array[i].
 *
 * Checks array[i] and sets tokens[i]->token_type to PIPE,
 * REDIRECT_IN_CHAR_HEREDOC, REDIRECT_OUT_CHAR_APPEND,
 * REDIRECT_IN_CHAR, REDIRECT_OUT_CHAR, or UNDEFINED.
 *
 * @param array Array of token strings.
 * @param tokens Array of t_token pointers.
 * @param i Index of the token to process.
 */
static void	first_token_assign(char **array, t_token **tokens, size_t i)
{
	if (!ft_strncmp(array[i], "<<", ft_strlen("<<"))
		&& ft_strlen(array[i]) == ft_strlen("<<"))
		tokens[i]->token_type = REDIRECT_IN_CHAR_HEREDOC;
	else if (!ft_strncmp(array[i], ">>", ft_strlen(">>"))
		&& ft_strlen(array[i]) == ft_strlen(">>"))
		tokens[i]->token_type = REDIRECT_OUT_CHAR_APPEND;
	else if (!ft_strncmp(array[i], "|", ft_strlen("|"))
		&& ft_strlen(array[i]) == ft_strlen("|"))
		tokens[i]->token_type = PIPE;
	else if (!ft_strncmp(array[i], "<", ft_strlen("<"))
		&& ft_strlen(array[i]) == ft_strlen("<"))
		tokens[i]->token_type = REDIRECT_IN_CHAR;
	else if (!ft_strncmp(array[i], ">", ft_strlen(">"))
		&& ft_strlen(array[i]) == ft_strlen(">"))
		tokens[i]->token_type = REDIRECT_OUT_CHAR;
	else
		tokens[i]->token_type = UNDEFINED;
}

/**
 * @brief Parses an array of strings into t_token pointers.
 *
 * Allocates and initializes an array of t_token pointers from the input
 * string array. Each t_token is allocated and its 'string' member is set
 * to the corresponding string. Calls first_token_assign() for each token.
 * On allocation failure, frees all previously allocated memory.
 *
 * @param array Array of strings to parse.
 * @param size Number of elements in array.
 * @return Array of t_token pointers, or NULL on failure.
 */
static t_token	**first_token_parse(char **array, size_t size)
{
	size_t	i;
	t_token	**tokens;

	tokens = ft_calloc(size + 1, sizeof(t_token *));
	if (!tokens)
		return (ft_matrix_free((void ***)&array, 0), NULL);
	i = 0;
	while (i < size)
	{
		tokens[i] = ft_calloc(1, sizeof(t_token));
		if (!tokens[i])
			return (free_tokens(tokens), ft_matrix_free((void ***)&array, 0),
				NULL);
		tokens[i]->string = ft_strdup(array[i]);
		if (!tokens[i]->string)
			return (free_tokens(tokens), ft_matrix_free((void ***)&array, 0),
				NULL);
		first_token_assign(array, tokens, i);
		i++;
	}
	return (tokens);
}

/**
 * @brief Classifies the type of a token argument by context.
 *
 * Analyzes the token at index `i` in `tokens`. If its type is
 * `UNDEFINED`, determines its type by inspecting the previous token:
 *
 * - If preceded by `REDIRECT_IN_CHAR`, sets type to `REDIRECT_IN_ROUTE`.
 *
 * - If preceded by `REDIRECT_OUT_CHAR` or `REDIRECT_OUT_CHAR_APPEND`,
 *   sets type to `REDIRECT_OUT_ROUTE`.
 *
 * - If preceded by `REDIRECT_IN_CHAR_HEREDOC`, sets type to `HEREDOC_EOF`.
 *
 * - If preceded by `COMMAND_BUILT_IN`, `COMMAND_ROUTE`, or `ARGUMENT`,
 *   sets type to `ARGUMENT`.
 *
 * - Otherwise, delegates to `cmd_resolver`.
 *
 * @param tokens Array of token pointers.
 * @param i Index of the token to classify.
 */
static void	arg_classification(t_token **tokens, size_t i)
{
	if (tokens[i]->token_type == UNDEFINED)
	{
		if (i > 0 && tokens[i - 1]->token_type == REDIRECT_IN_CHAR)
			tokens[i]->token_type = REDIRECT_IN_ROUTE;
		else if (i > 0 && (tokens[i - 1]->token_type == REDIRECT_OUT_CHAR
				|| tokens[i - 1]->token_type == REDIRECT_OUT_CHAR_APPEND))
			tokens[i]->token_type = REDIRECT_OUT_ROUTE;
		else if (i > 0 && tokens[i - 1]->token_type == REDIRECT_IN_CHAR_HEREDOC)
			tokens[i]->token_type = HEREDOC_EOF;
		else if (i > 0 && (tokens[i - 1]->token_type == COMMAND_BUILT_IN
				|| tokens[i - 1]->token_type == COMMAND_ROUTE || tokens[i
					- 1]->token_type == COMMAND_NOT_FOUND || tokens[i
					- 1]->token_type == ARGUMENT))
			tokens[i]->token_type = ARGUMENT;
		else
			cmd_resolver(tokens, i);
	}
}

t_token	**tokenize(char **array)
{
	size_t	size;
	size_t	i;
	t_token	**tokens;

	size = ft_matrix_len((void **)array);
	tokens = first_token_parse(array, size);
	i = 0;
	while (i < size)
	{
		arg_classification(tokens, i);
		++i;
	}
	return (tokens);
}
