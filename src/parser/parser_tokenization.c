/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:21:57 by pablo             #+#    #+#             */
/*   Updated: 2025/11/12 21:29:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/types.h>

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
			return (free_tokens(&tokens), ft_matrix_free((void ***)&array, 0),
				NULL);
		tokens[i]->string = ft_strdup(array[i]);
		if (!tokens[i]->string)
			return (free_tokens(&tokens), ft_matrix_free((void ***)&array, 0),
				NULL);
		first_token_assign(array, tokens, i);
		i++;
	}
	return (tokens);
}

/**
 * @brief Resolves argument classification using previous tokens.
 *
 * Backtracks from index `i - 1` and inspects tokens until a pipe or the
 * beginning is reached. Updates tokens[i]->token_type when a relevant
 * context (redirection, heredoc, command or argument) is detected.
 *
 * @param tokens Array of token pointers.
 * @param i Current token index.
 */
static void	argument_resolver(t_token **tokens, size_t i)
{
	ssize_t	j;

	if (i == 0)
		return ;
	j = (ssize_t)i - 1;
	if (tokens[j]->token_type == REDIRECT_IN_CHAR)
		return (tokens[i]->token_type = REDIRECT_IN_ROUTE, (void)0);
	if (tokens[j]->token_type == REDIRECT_OUT_CHAR
		|| tokens[j]->token_type == REDIRECT_OUT_CHAR_APPEND)
		return (tokens[i]->token_type = REDIRECT_OUT_ROUTE, (void)0);
	if (tokens[j]->token_type == REDIRECT_IN_CHAR_HEREDOC)
		return (tokens[i]->token_type = HEREDOC_EOF, (void)0);
	if (tokens[j]->token_type == REDIRECT_IN_ROUTE
		|| tokens[j]->token_type == REDIRECT_OUT_ROUTE
		|| tokens[j]->token_type == HEREDOC_EOF
		|| tokens[j]->token_type == COMMAND_BUILT_IN
		|| tokens[j]->token_type == COMMAND_ROUTE
		|| tokens[j]->token_type == COMMAND_NOT_FOUND
		|| tokens[j]->token_type == ARGUMENT)
		return (tokens[i]->token_type = ARGUMENT, (void)0);
}

/**
 * @brief Classifies a token as either an argument or a command if its
 * type is undefined.
 *
 * This function attempts to resolve the type of a token at the specified
 * index in the tokens array. If the token's type is UNDEFINED, it first
 * tries to resolve it as an argument using argument_resolver. If the
 * token remains UNDEFINED after that, it then attempts to resolve it as
 * a command using cmd_resolver.
 *
 * @param tokens A pointer to an array of token pointers.
 * @param i The index of the token to classify in the tokens array.
 */
static void	arg_classification(t_token **tokens, size_t i)
{
	if (tokens[i]->token_type == UNDEFINED)
	{
		argument_resolver(tokens, i);
		if (tokens[i]->token_type == UNDEFINED)
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
