/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:38:12 by pablo             #+#    #+#             */
/*   Updated: 2025/09/27 20:35:51 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

extern char				**environ;
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

/**
 * @brief Generates a colored shell prompt string.
 *
 * Constructs a shell prompt that includes the shell name ("Minishell"),
 * the current user's username, and the current working directory, all with
 * color formatting. The prompt is dynamically allocated and must be freed by
 * the caller.
 *
 * The format of the prompt is:
 *
 * [YELLOW]Minishell[RED]@[BLUE][USER][RESET] [GREEN][CWD][RESET] -->
 *
 * @return char* Pointer to the dynamically allocated prompt string on success,
 *               or NULL if a memory allocation or system call fails.
 */
char	*get_shell_prompt(void)
{
	char	*base_prompt;
	char	*colored_prompt;
	char	*current_dir;
	char	*prompt_with_cwd;
	char	*final_prompt;

	base_prompt = ft_strjoin(YELLOW "Minishell" RED "@" BLUE, getenv("USER"));
	if (!base_prompt)
		return (NULL);
	colored_prompt = ft_strjoin(base_prompt, RESET " " GREEN);
	ft_free((void **)&base_prompt);
	if (!colored_prompt)
		return (NULL);
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_free((void **)&colored_prompt), NULL);
	prompt_with_cwd = ft_strjoin(colored_prompt, current_dir);
	ft_free((void **)&colored_prompt);
	ft_free((void **)&current_dir);
	if (!prompt_with_cwd)
		return (NULL);
	final_prompt = ft_strjoin(prompt_with_cwd, RESET " --> ");
	ft_free((void **)&prompt_with_cwd);
	return (final_prompt);
}

// TODO Eliminar el tmp del heredoc
int	main(int argc, char **argv, char **envp)
{
	char			*input;
	char			**get_full_cmd;
	t_shell_data	shell_data;
	char			*prompt;

	init_shell_data(&shell_data);
	init_minishell();
	block_terminal_signals();
	prompt = NULL;
	while (1)
	{
		/**
			* @note Guarreo de prueba,
				ver como pablo pilla las variables de entorno.
			*/
		if (isatty(STDIN_FILENO))
		{
			prompt = get_shell_prompt();
			if (!prompt)
				return (free_shell_data(&shell_data), 1);
			input = readline(prompt);
		}
		else
			// TODO: Get_next_line no funciona bien por el buffer estático y por no manejar multiples fds.
			input = ft_get_next_line(STDIN_FILENO);
		if (input == NULL)
			return (rl_clear_history(), free_shell_data(&shell_data),
				EXIT_SUCCESS);
		shell_data.tokens = parse(input, shell_data.shell_envi.ordered_envp);
		if (shell_data.tokens)
		{
			shell_data.einfo = get_entry_info(shell_data.tokens);
			add_history(input);
			//free(input);
			// Analyze each element
			// TODO: Este for tiene que ser un while
			for (int i = 0; shell_data.tokens[i]; i++)
			{
				printf("%s : %s\n", shell_data.tokens[i]->string,
					token_strings[shell_data.tokens[i]->token_type]);
			}
			printf("/////////////////////////////////////\n");
			execution_cycle(&shell_data);
			// liberar cosas de get_entry_info
		}

		free(input);
		free_tokens(shell_data.tokens);
		ft_free((void **)&prompt);
	}
}
