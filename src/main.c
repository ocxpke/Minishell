/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:38:12 by pablo             #+#    #+#             */
/*   Updated: 2025/07/31 13:58:53 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		printf("|%s|\n", matrix[i]);
		i++;
	}
}

static char	*get_token_type_name(t_ttype type)
{
	if (type == ARGUMENT)
		return ("ARGUMENT");
	else if (type == COMMAND_ROUTE)
		return ("COMMAND_ROUTE");
	else if (type == COMMAND_BUILT_IN)
		return ("COMMAND_BUILT_IN");
	else if (type == HEREDOC_EOF)
		return ("HEREDOC_EOF");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIRECT_IN_CHAR)
		return ("REDIRECT_IN_CHAR");
	else if (type == REDIRECT_IN_CHAR_HEREDOC)
		return ("REDIRECT_IN_CHAR_HEREDOC");
	else if (type == REDIRECT_OUT_CHAR)
		return ("REDIRECT_OUT_CHAR");
	else if (type == REDIRECT_OUT_CHAR_APPEND)
		return ("REDIRECT_OUT_CHAR_APPEND");
	else if (type == REDIRECT_IN_ROUTE)
		return ("REDIRECT_IN_ROUTE");
	else if (type == REDIRECT_OUT_ROUTE)
		return ("REDIRECT_OUT_ROUTE");
	else if (type == UNDEFINED)
		return ("UNDEFINED");
	else if (type == COMMAND_NOT_FOUND)
		return("COMMAND_NOT_FOUND");
	else
		return ("UNKNOWN");
}

void	print_token_matrix(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
	{
		printf("Token matrix is NULL\n");
		return ;
	}
	printf("=== TOKEN MATRIX DEBUG ===\n");
	while (tokens[i])
	{
		printf("[%d] String: |%s| -> Type: %s\n", i,
			tokens[i]->string ? tokens[i]->string : "NULL",
			get_token_type_name(tokens[i]->token_type));
		i++;
	}
	printf("=== END TOKEN MATRIX ===\n");
}

void	print_single_token(t_token *token, int index)
{
	if (!token)
	{
		printf("Token[%d] is NULL\n", index);
		return ;
	}
	printf("=== SINGLE TOKEN DEBUG ===\n");
	printf("Index: %d\n", index);
	printf("String: |%s|\n", token->string ? token->string : "NULL");
	printf("Type: %s\n", get_token_type_name(token->token_type));
	printf("=== END SINGLE TOKEN ===\n");
}

int	main(void)
{
	t_token	**tokens;

	tokens = parse("cat $HOME$USER | patata > 4 | echo");
	print_token_matrix(tokens);
	free_tokens(tokens);
	return (0);
}
