/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:38:12 by pablo             #+#    #+#             */
/*   Updated: 2025/11/05 18:37:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Seguir limpiando código desde init_shell_data.
// TODO: Implementar nuevo get_next_line corregido.

#include "colors.h"
#include "minishell.h"

extern char				**environ;
volatile sig_atomic_t	g_signal_recv = 0;

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

static int	ctrl_d_exit(t_shell_data *shell_data)
{
	int		ret_num;
	char	*exit_env_value;

	exit_env_value = get_enviroment_value("FT_EXIT_ENV",
			shell_data->shell_envi.envp);
	if (!exit_env_value)
		ret_num = 1;
	else
		ret_num = ft_atoi(exit_env_value);
	rl_clear_history();
	free_shell_data(shell_data);
	return (ret_num);
}

int	main()
{
	char			*input;
	t_shell_data	shell_data;
	char			*prompt;

	init_shell_data(&shell_data);
	block_terminal_signals();
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			prompt = get_shell_prompt(shell_data.shell_envi.ordered_envp);
			if (!prompt)
				prompt = ft_strdup("Minishell --> ");// TODO: Si no hay env se tiene que ejecutar la minishell, no cerrar
			input = readline(prompt);
			ft_free((void **)&shell_data.prompt);// TODO: por que esta promt en shell en v y como una variable simple??
			shell_data.prompt = prompt;
		}
		else
		{
			input = ft_get_next_line(STDIN_FILENO);
			if (input)
				clean_input(input);
		}
		if (input == NULL)
			return (ctrl_d_exit(&shell_data));
		shell_data.tokens = parse(input, shell_data.shell_envi.ordered_envp);
		if (shell_data.tokens)
		{
			shell_data.einfo = get_entry_info(shell_data.tokens);
			shell_data.tokens = NULL;
			add_history(input);
			//debug_shell_info(&shell_data);
			execution_cycle(&shell_data);
		}
		free(input);
		clean_entry_info(&shell_data.einfo);
	}
}
