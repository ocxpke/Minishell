/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:24:40 by pablo             #+#    #+#             */
/*   Updated: 2025/11/09 15:15:57 by pablo            ###   ########.fr       */
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
	cinfo->array_size = args_count + 1;
	cinfo->cmd_and_args = ft_calloc(args_count + 2, sizeof(char *));
	if (!cinfo->cmd_and_args)
		return (1);
	cinfo->cmd_and_args[0] = ft_strdup(tokens[cmd_pos]->string);
	if (!cinfo->cmd_and_args[0])
		return (1);
	i = 1;
	while (i < args_count + 1)
	{
		cinfo->cmd_and_args[i] = ft_strdup(tokens[cmd_pos + i]->string);
		if (!cinfo->cmd_and_args[i])
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
	cinfo->cmd_and_args = NULL;
	cinfo->input_file = NULL;
	cinfo->is_append = -1;
	cinfo->is_heredoc = -1;
	cinfo->output_file = NULL;
	cinfo->array_size = 0;
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
	size_t		i;
	int			token_pos;
	t_token		**pipe;

	i = 0;
	while (i < n_commands)
	{
		cinfos[i] = initialize_cinfo();
		if (!cinfos[i] || !get_next_command(tokens, i, &token_pos))
			return (1);
		if (set_cinfo_args(tokens, cinfos[i], token_pos))
			return (1);
		pipe = find_next_pipe_pos_after_command(tokens + token_pos);
		if (set_command_input_file(tokens + token_pos, cinfos[i], pipe)
			|| set_command_output_file(tokens + token_pos, cinfos[i], pipe))
			return (1);
		++i;
	}
	return (0);
}

void	clean_cinfos(t_cinfo **cinfos)
{
	size_t	i;

	i = 0;
	while (cinfos[i])
	{
		if (cinfos[i]->is_heredoc && cinfos[i]->input_file)
			unlink(cinfos[i]->input_file);
		if (cinfos[i]->cmd_and_args)
			ft_matrix_free((void ***)&cinfos[i]->cmd_and_args, 0);
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
