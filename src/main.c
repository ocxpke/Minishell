/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:38:12 by pablo             #+#    #+#             */
/*   Updated: 2025/08/18 13:48:12 by pablo            ###   ########.fr       */
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

/*
int	main(void)
{
	t_token	**tokens;

	tokens = parse("echo $HOME$USER | patata > 4");
	print_token_matrix(tokens);
	free_tokens(tokens);
	return (0);
}
	*/
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
	ret = ft_calloc(nmeb, sizeof(char *));
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

//TODO Eliminar el tmp del heredoc
int	main(int argc, char **argv, char **envp)
{
	t_token	**tokens;
	pid_t	pid_fork;
	char	*input;
	char	**get_full_cmd;
	char	*heredoc_buffer;
	t_einfo *einfo;

	(void)argv;
	(void)argc;
	ignore_terminal_signals();
	heredoc_buffer = NULL;
	while (1)
	{
		input = readline("--> ");
		if (input == NULL)
			return (rl_clear_history(), EXIT_SUCCESS);
		tokens = parse(input);
		// Gitanaada
		if (!tokens)
			continue ;
		einfo = get_entry_info(tokens);
		add_history(input);
		if (!ft_strncmp(tokens[0]->string, "exit",
				ft_strlen(tokens[0]->string)))
			return (free_tokens(tokens), rl_clear_history(), EXIT_SUCCESS);
		// Solo para informar
		for (int i = 0; tokens[i]; i++)
		{
			printf("%s : %s\n", tokens[i]->string,
				get_token_type_name(tokens[i]->token_type));
			printf("\n/////////////////////////////////////\n");
		}
		fflush(stdout); // Forzar que se imprima el buffer
		get_full_cmd = get_full_command(tokens);
		pid_fork = fork();
		if (pid_fork == -1)
			exit(EXIT_FAILURE);
		if (pid_fork == 0)
		{
			// Creo que necesitamos env por que nos pueden pasar las cosas sin
			// variables de entornos o variables de entorono modificadas
			restore_terminal_signals();
			if (get_full_cmd[0] != NULL)
				execve(get_full_cmd[0], get_full_cmd, envp);
			free_full_command(get_full_cmd);
			exit(EXIT_FAILURE);
		}
		else
		{
			// Ctrl+z suspende un proceso-- > implica controol de tareas-- > no hacer nada,no ?
			waitpid(pid_fork, NULL, 0);
			free_full_command(get_full_cmd);
		}
	}
}
