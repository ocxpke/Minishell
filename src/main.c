/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:38:12 by pablo             #+#    #+#             */
/*   Updated: 2025/11/12 17:25:38 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

extern char				**environ;
volatile sig_atomic_t	g_signal_recv = 0;

/**
 * Cleans the input string by null-terminating it at the first occurrence
 * of a non-printable character or a newline character.
 *
 * This function iterates through the input string and replaces the first
 * non-printable character (as determined by ft_isprint) or newline ('\n')
 * with a null terminator ('\0'), effectively truncating the string at that
 * point. If no such character is found, the string remains unchanged.
 *
 * @param input A pointer to the null-terminated string to be cleaned.
 *              The string is modified in place.
 */
static void	clean_input(char *input)
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

/**
 * Handles the exit process triggered by Ctrl+D in the minishell.
 *
 * This function retrieves the value of the "FT_EXIT_ENV" environment
 * variable to determine the exit status. If the variable is not set, it
 * defaults to 1. It then clears the readline history, frees the shell
 * data, and returns the exit status.
 *
 * @param shell_data A pointer to the shell data structure containing
 *                   environment and other shell-related information.
 * @return The exit status code, either from the environment variable or
 *         1 if not set.
 */
static int	ctrl_d_exit(t_shell_data *shell_data)
{
	int		ret_num;
	char	*exit_env_value;

	exit_env_value = get_env_value("FT_EXIT_ENV",
			shell_data->shell_envi.envp);
	if (!exit_env_value)
		ret_num = 1;
	else
		ret_num = ft_atoi(exit_env_value);
	rl_clear_history();
	free_shell_data(shell_data);
	return (ret_num);
}

/**
 * @brief Reads shell input from stdin, handling both interactive (tty)
 *        and non-interactive modes.
 *
 * In interactive mode (when stdin is a tty), this function generates or
 * retrieves a prompt, then uses readline to read a line of input. In
 * non-interactive mode, it reads a line using ft_get_next_line and
 * cleans the input.
 *
 * @param shell_data Pointer to the shell data structure containing
 *                   environment and prompt info.
 * @param input Pointer to a char pointer where the read input will be
 *              stored.
 * @return 1 if input was successfully read, 0 if end of input (NULL)
 *         was reached.
 */
static int	read_shell_input(t_shell_data *shell_data, char **input)
{
	if (isatty(STDIN_FILENO))
	{
		ft_free((void **)&shell_data->prompt);
		shell_data->prompt = get_prompt(shell_data->shell_envi.ordered_envp);
		if (!shell_data->prompt)
			shell_data->prompt = ft_strdup("Minishell --> ");
		*input = readline(shell_data->prompt);
	}
	else
	{
		*input = ft_get_next_line(STDIN_FILENO);
		if (*input)
			clean_input(*input);
	}
	if (*input == NULL)
		return (0);
	return (1);
}

/**
 * @brief Executes a single shell cycle by parsing the input, retrieving
 *        entry information, and proceeding to the execution phase if
 *        successful.
 *
 * This function takes the user input, parses it into tokens, obtains entry
 * information for execution, handles any errors during parsing or entry
 * info creation, adds the input to the command history, and initiates the
 * execution cycle.
 *
 * @param shell_data Pointer to the shell data structure containing
 *                   environment and state.
 * @param input The user input string to be processed.
 *
 * @note If parsing fails, an error is printed and the function returns
 *       early. If entry info creation fails, an error is printed, tokens
 *       are freed, and the function returns. The tokens are set to NULL
 *       after successful entry info retrieval.
 */
static void	execute_shell_cycle(t_shell_data *shell_data, char *input)
{
	shell_data->tokens = parse(input, shell_data->shell_envi.ordered_envp);
	if (shell_data->tokens)
	{
		shell_data->einfo = get_entry_info(shell_data->tokens);
		if (!shell_data->einfo)
		{
			perror("Error creating Entry Info");
			free_tokens(&shell_data->tokens);
			shell_data->tokens = NULL;
			add_history(input);
			return ;
		}
		shell_data->tokens = NULL;
		add_history(input);
		execution_cycle(shell_data);
	}
}

int	main(void)
{
	char			*input;
	t_shell_data	shell_data;

	init_shell_data(&shell_data);
	block_terminal_signals();
	while (1)
	{
		g_signal_recv = 0;
		if (!read_shell_input(&shell_data, &input))
			return (ctrl_d_exit(&shell_data));
		execute_shell_cycle(&shell_data, input);
		free(input);
		clean_entry_info(&shell_data.einfo);
	}
}
