/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:38:12 by pablo             #+#    #+#             */
/*   Updated: 2025/10/27 10:47:33 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Seguir limpiando código desde init_shell_data.
// TODO: Implementar nuevo get_next_line corregido.

#include "colors.h"
#include "minishell.h"

extern char				**environ;
volatile sig_atomic_t	signal_recv = 0;

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

/**
 * @brief Cleans the input string by replacing the first non-printable character
 *        or newline character with a null terminator.
 *
 * This function iterates through the input string and checks each character.
 * If a character is not printable (as determined by ft_isprint) or is a newline
 * character ('\n'), it replaces that character with a null terminator ('\0')
 * and returns, effectively truncating the string at that point.
 *
 * @param input Pointer to the input string to be cleaned.
 */
void	clean_input(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isprint(input[i]) || input[i] == '\n')
		{
			input[i] = 0;
			return ;
		}
		++i;
	}
}

// TODO Eliminar el tmp del heredoc
int	main(int argc, char **argv, char **envp)
{
	char			*input;
	//char			**get_full_cmd;
	(void)argc;
	(void)argv;
	(void)envp;
	t_shell_data	shell_data;
	char			*prompt;

	init_shell_data(&shell_data);
	block_terminal_signals();
	prompt = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			prompt = get_shell_prompt();
			if (!prompt)
				return (free_shell_data(&shell_data), 1);
			input = readline(prompt);
		}
		else
		{
			input = ft_get_next_line(STDIN_FILENO);
			if (input)
				clean_input(input);
		}
		if (input == NULL)
			return (rl_clear_history(), ft_free((void **)&prompt), free_shell_data(&shell_data),
				EXIT_SUCCESS);
		shell_data.tokens = parse(input, shell_data.shell_envi.ordered_envp);
		if (shell_data.tokens)
		{
			shell_data.einfo = get_entry_info(shell_data.tokens);
			add_history(input);
			// TODO: Este for se elimina antes de entregar
			/* for (int i = 0; shell_data.tokens[i]; i++)
			{
				printf("%s : %d\n", shell_data.tokens[i]->string,
					shell_data.tokens[i]->token_type);
			}
			printf("/////////////////////////////////////\n"); */
			debug_shell_info(&shell_data);
			execution_cycle(&shell_data);
		}
		free(input);
		free_tokens(shell_data.tokens);
		ft_free((void **)&prompt);
	}
}
