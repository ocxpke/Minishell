/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:38:12 by pablo             #+#    #+#             */
/*   Updated: 2025/08/18 14:48:32 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

extern char				**environ;
/*
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

	tokens = parse("echo $HOME$USER | patata > 4");
	print_token_matrix(tokens);
	free_tokens(tokens);
	return (0);
}
	*/

volatile sig_atomic_t	signal_recv = 0;

/**
 * @note Me da el comando + todos los argumentos, todo lo demas lo omite
 */
char	**get_full_command(t_token **token)
{
	char	**ret;
	int		nmeb;
	int		i;

	nmeb = 0;
	while (token[nmeb] && ((token[nmeb]->token_type == COMMAND_ROUTE)
			|| (token[nmeb]->token_type == COMMAND_BUILT_IN)
			|| (token[nmeb]->token_type == ARGUMENT)))
		nmeb++;
	if (nmeb == 0)
		return (NULL);
	ret = ft_calloc(nmeb + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nmeb)
	{
		ret[i] = ft_strdup(token[i]->string);
		i++;
	}
	return (ret);
}

void	free_full_command(char **command)
{
	int	i;

	i = 0;
	if (command == NULL)
		return ;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
	command = NULL;
}

void	init_minishell(void)
{
	if (!isatty(STDIN_FILENO))
	{
		// En este caso ejecutamos el archivo que nos hayan pasado linea a linea GNL.
		// Tenemos que leer el archivo de entrada linea a linea y ejcutarlo linea a linea
		printf("No es una entrada interactiva\n");
	}
}

// TODO Eliminar el tmp del heredoc
int	main(int argc, char **argv, char **envp)
{
	char			*input;
	char			**get_full_cmd;
	char			*heredoc_buffer;
	t_einfo			*einfo;
	t_shell_data	shell_data;

	init_shell_data(&shell_data);
	init_minishell();
	block_terminal_signals();
	while (1)
	{
		printf("%sMinishell%s@%s%s%s", YELLOW, RED, BLUE, getenv("USER"),
			RESET);
		/**
			* @note Guarreo de prueba,
				ver como pablo pilla las variables de entorno.
			*/
		if (isatty(STDIN_FILENO))
			input = readline("--> ");
		else
			input = ft_get_next_line(STDIN_FILENO);
		if (input == NULL)
			return (rl_clear_history(), free_shell_data(&shell_data),
				EXIT_SUCCESS);
		shell_data.tokens = parse(input);
		if (shell_data.tokens)
		{
			einfo = get_entry_info(shell_data.tokens);
			add_history(input);
			free(input);
			// Analyze each element
			for (int i = 0; shell_data.tokens[i]; i++)
			{
				printf("%s : %s\n", shell_data.tokens[i]->string,
					token_strings[shell_data.tokens[i]->token_type]);
			}
			printf("/////////////////////////////////////\n");
			execution_cycle(&shell_data);
		}
		else
			free(input);
		free_tokens(shell_data.tokens);
	}
}
