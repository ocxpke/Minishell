/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set_commands_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:24:40 by pablo             #+#    #+#             */
/*   Updated: 2025/09/27 19:09:55 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_command(t_token **tokens, int n, int *token_pos)
{
	int	cmd_count;
	int	i;

	cmd_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->token_type == COMMAND_BUILT_IN
			|| tokens[i]->token_type == COMMAND_ROUTE
			|| tokens[i]->token_type == COMMAND_NOT_FOUND)
		{
			if (cmd_count == n)
			{
				if (token_pos != NULL)
					*token_pos = i;
				return (tokens[i]);
			}
			cmd_count++;
		}
		++i;
	}
	if (token_pos != NULL)
		*token_pos = -1;
	return (NULL);
}

/**
 * Counts the number of argument tokens following a command token.
 *
 * @param tokens   Array of pointers to t_token structures.
 * @param cmd_pos  Index of the command token in the array.
 * @return         Number of consecutive argument tokens after the command.
 */
int	count_command_args(t_token **tokens, int cmd_pos)
{
	int	args_count;

	args_count = 0;
	++cmd_pos;
	while (tokens[cmd_pos] && tokens[cmd_pos]->token_type == ARGUMENT)
	{
		args_count++;
		cmd_pos++;
	}
	return (args_count);
}

/**
 * @brief Fills an array with the command and its args.
 *
 * Locates the command token at the specified index and fills cmd_array with
 * the command string followed by its argument strings. The array is
 * terminated with a NULL pointer. Only tokens of type ARGUMENT are added
 * as arguments after the command.
 *
 * @tokens:    Array of t_token pointers representing the tokenized input.
 * @cmd_array: Array of strings to fill with the command and its arguments.
 * @n_cmd:     Index of the command to process within the tokens array.
 * @size:      Max number of arguments (including the command) to fill.
 */
void	set_command_and_arguments(t_token **tokens, char **cmd_array, int n_cmd,
		int size)
{
	t_token	*cmd_token;
	int		i;
	int		token_pos;

	cmd_token = get_next_command(tokens, n_cmd, &token_pos);
	cmd_array[0] = ft_strdup(cmd_token->string);
	i = 1;
	while (i < size)
	{
		token_pos++;
		if (tokens[token_pos]->token_type == ARGUMENT)
		{
			cmd_array[i] = ft_strdup(tokens[token_pos]->string);
			++i;
		}
	}
	cmd_array[i] = NULL;
}

/**
 * @brief Allocates and initializes an array of command argument arrays.
 *
 * Iterates through the list of commands, allocating memory for each
 * command's argument array and populating it using helper functions.
 * Handles memory allocation failures by freeing any previously allocated
 * memory and returning NULL.
 *
 * @param tokens: Double pointer to the list of tokens representing the parsed
 * input.
 * @param command_count: The total number of commands to process.
 * @param commands: Triple pointer to the array where command argument arrays
 * will be stored.
 *
 * @return Pointer to the array of command argument arrays on success,
 * or NULL on failure.
 */
static char	***set_commands_loop(t_token **tokens, int command_count,
		char ***commands)
{
	int	i;
	int	cmd_pos;
	int	command_size;

	i = 0;
	while (i < command_count)
	{
		get_next_command(tokens, i, &cmd_pos);
		command_size = (count_command_args(tokens, cmd_pos) + 1);
		commands[i] = malloc(sizeof(char *) * (command_size + 1));
		if (!commands[i])
		{
			while (i > 0)
				free(commands[--i]);
			free(commands);
			return (NULL);
		}
		set_command_and_arguments(tokens, commands[i], i, command_size);
		++i;
	}
	return (commands);
}

// TODO: los command not found tienen que entrar en commands*
char	***get_commands(t_token **tokens)
{
	char	***commands;
	int		command_count;

	command_count = count_tokens(tokens, COMMAND_BUILT_IN)
		+ count_tokens(tokens, COMMAND_ROUTE) + count_tokens(tokens,
			COMMAND_NOT_FOUND);
	commands = malloc((sizeof(char **) * command_count) + 1);
	if (!commands)
		return (NULL);
	commands[command_count] = NULL;
	commands = set_commands_loop(tokens, command_count, commands);
	return (commands);
}
