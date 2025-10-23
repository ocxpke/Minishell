/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:24:40 by pablo             #+#    #+#             */
/*   Updated: 2025/10/26 13:28:07 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Hay codigo de jose que usa tokens. cinfo deberia tener duplicados
// No el token original para liberarlo al temrinar de parsear todo.

/**
 * @brief Sets the arguments for a command info structure from tokens.
 *
 * This function allocates memory for the arguments array in the command info
 * structure and populates it with strings from the token list, starting from
 * the position after the command position.
 *
 * @param tokens A pointer to an array of token pointers.
 * @param cinfo A pointer to the command info structure to update.
 * @param cmd_pos The position of the command token in the tokens array.
 * @return 0 on success, 1 if memory allocation fails.
 */
static int	set_cinfo_args(t_token **tokens, t_cinfo *cinfo, int cmd_pos)
{
	int	args_count;
	int	i;

	args_count = count_command_args(tokens, cmd_pos);
	cinfo->args = ft_calloc(args_count + 1, sizeof(char *));
	if (!cinfo->args)
		return (1);
	i = 0;
	while (i < args_count)
	{
		cinfo->args[i] = ft_strdup(tokens[cmd_pos + 1 + i]->string);
		if (!cinfo->args[i])
			return (1);
		++i;
	}
	return (0);
}

/**
 * @brief Initializes a new t_cinfo structure.
 *
 * This function allocates memory for a t_cinfo structure and initializes
 * all its members to default values: NULL for pointer fields and -1 for
 * integer flags.
 *
 * @return A pointer to the newly initialized t_cinfo structure, or NULL if
 *         memory allocation fails.
 */
static t_cinfo	*initialize_cinfo(void)
{
	t_cinfo	*cinfo;

	cinfo = malloc(sizeof(t_cinfo));
	if (!cinfo)
		return (NULL);
	cinfo->args = NULL;
	cinfo->command = NULL;
	cinfo->input_file = NULL;
	cinfo->is_append = -1;
	cinfo->is_heredoc = -1;
	cinfo->output_file = NULL;
	return (cinfo);
}

/**
 * @brief Sets up command information structures for each command in the
 * token list.
 *
 * This function iterates through the specified number of commands,
 * allocating and initializing a t_cinfo structure for each. It extracts
 * the command string, sets arguments, input file, and output file for
 * each command based on the token array. If setting arguments fails, it
 * returns an error code.
 *
 * @param tokens Pointer to the array of tokens representing the parsed
 * input.
 * @param cinfos Pointer to the array where command info structures will
 * be stored.
 * @param n_commands The number of commands to process.
 * @return 0 on success, 1 on failure (e.g., if setting arguments fails).
 */
static int	set_cinfos_loop(t_token **tokens, t_cinfo **cinfos,
		size_t n_commands)
{
	size_t	i;
	int		token_pos;
	t_token	*cmd_token;

	i = 0;
	while (i < n_commands)
	{
		cinfos[i] = initialize_cinfo();
		if (!cinfos[i])
			return (1);
		cmd_token = get_next_command(tokens, i, &token_pos);
		if (!cmd_token)
			return (1);
		cinfos[i]->command = ft_strdup(cmd_token->string);
		if (!cinfos[i]->command)
			return (1);
		if (set_cinfo_args(tokens, cinfos[i], token_pos))
			return (1);
		if (token_pos > 0)
			--token_pos;
		if (set_command_input_file(tokens + token_pos, cinfos[i])
			|| set_command_output_file(tokens + token_pos, cinfos[i]))
			return (1);
		++i;
	}
	return(0);
}

void	clean_cinfos(t_cinfo **cinfos)
{
	size_t	i;

	i = 0;
	while (cinfos[i])
	{
		if (cinfos[i]->args)
			ft_matrix_free((void ***)&cinfos[i]->args, 0);
		ft_free((void **)&(cinfos[i]->command));
		ft_free((void **)&(cinfos[i]->input_file));
		ft_free((void **)&(cinfos[i]->output_file));
		ft_free((void **)&(cinfos[i]));
		++i;
	}
	ft_free((void **)&cinfos);
}

int	set_cinfos(t_token **tokens, t_einfo *einfo)
{
	size_t	n_commands;

	// TODO: Quizás sería mejor que count_tokens fuese variádico;
	n_commands = count_tokens(tokens, COMMAND_BUILT_IN) + count_tokens(tokens,
			COMMAND_NOT_FOUND) + count_tokens(tokens, COMMAND_ROUTE);
	einfo->cinfos = malloc(sizeof(t_cinfo *) * (n_commands + 1));
	if (!einfo->cinfos)
		return (1);
	if (set_cinfos_loop(tokens, einfo->cinfos, n_commands))
		return (clean_cinfos(einfo->cinfos), 1);
	einfo->cinfos[n_commands] = NULL;
	return (0);
}
