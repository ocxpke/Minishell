/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_resolver.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:08:16 by pablo             #+#    #+#             */
/*   Updated: 2025/11/13 21:45:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Checks if the given command string matches one of the built-in shell
 *        commands.
 *
 * Supported built-in commands:
 *
 * - echo
 *
 * - cd
 *
 * - pwd
 *
 * - export
 *
 * - unset
 *
 * - env
 *
 * - exit
 *
 *
 * @param cmd The command string to check.
 * @return 1 if the command is a built-in, 0 otherwise.
 */
static int	is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4) && (cmd[4] == '\0' || ft_isspace(cmd[4])))
		return (1);
	if (!ft_strncmp(cmd, "cd", 2) && (cmd[2] == '\0' || ft_isspace(cmd[2])))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 3) && (cmd[3] == '\0' || ft_isspace(cmd[3])))
		return (1);
	if (!ft_strncmp(cmd, "export", 6) && (cmd[6] == '\0' || ft_isspace(cmd[6])))
		return (1);
	if (!ft_strncmp(cmd, "unset", 5) && (cmd[5] == '\0' || ft_isspace(cmd[5])))
		return (1);
	if (!ft_strncmp(cmd, "env", 3) && (cmd[3] == '\0' || ft_isspace(cmd[3])))
		return (1);
	if (!ft_strncmp(cmd, "exit", 4) && (cmd[4] == '\0' || ft_isspace(cmd[4])))
		return (1);
	return (0);
}

/**
 * @brief Searches for a command in the given paths array.
 *
 * Iterates through the paths array, constructs full command paths by
 * appending the command name to each path, and checks if the resulting
 * path is executable. Returns the first executable path found.
 *
 * Note: This function does NOT free the paths array. The caller is
 * responsible for freeing paths after calling this function.
 *
 * @param paths Array of directory paths to search in (not freed by function).
 * @param cmd The command name to search for.
 * @return The full path to the executable command on success, or NULL if
 *         not found or on allocation failure.
 */
static char	*search_path(char **paths, char *cmd)
{
	char	*cmd_path;
	char	*tmp;
	size_t	i;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
		{
			errno = 0;
			return (cmd_path);
		}
		free(cmd_path);
		++i;
	}
	return (NULL);
}

/**
 * @brief Resolves whether a command token represents a literal path.
 *
 * If the token's string contains a '/', it is treated as a path:
 *
 *   - If the path is accessible and executable, sets token_type to
 *     COMMAND_NOT_FOUND and returns 0.
 *
 *   - Otherwise, sets token_type to COMMAND_ROUTE and returns 1.
 *
 * If the token's string does not contain a '/', returns 2.
 *
 * @param token Pointer to the command token to resolve.
 * @return 0 if the command is not found, 1 if the command is a route, 2
 *         otherwise.
 */
static int	cmd_literal_resolver(t_token *token)
{
	if (ft_strchr(token->string, '/') != NULL)
	{
		if (access(token->string, X_OK))
			return (token->token_type = COMMAND_NOT_FOUND, 0);
		return (token->token_type = COMMAND_ROUTE, 1);
	}
	return (2);
}

/**
 * @brief Resolves the full path of a command token using PATH env variable.
 *
 * Attempts to find the executable path for the command in the given token.
 * Retrieves PATH from linked_env, splits it into directories, and searches
 * for the command. If found, updates token->string and sets type to
 * COMMAND_ROUTE. If not found, sets type to COMMAND_NOT_FOUND.
 * If PATH is missing or allocation fails, sets type to UNDEFINED.
 *
 * @param token Pointer to the t_token structure to resolve.
 * @param linked_env Pointer to the linked environment list.
 */
static void	cmd_path_resolver(t_token *token, t_linked_env *linked_env)
{
	char	*env_path;
	char	**paths;
	char	*cmd_path;

	env_path = get_env_value("PATH", linked_env);
	if (!env_path)
		return (token->token_type = UNDEFINED, (void)0);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (token->token_type = UNDEFINED, (void)0);
	cmd_path = search_path(paths, token->string);
	ft_matrix_free((void ***)&paths, 0);
	if (cmd_path)
	{
		free(token->string);
		token->string = cmd_path;
		token->token_type = COMMAND_ROUTE;
		return ;
	}
	else
		return (token->token_type = COMMAND_NOT_FOUND, (void)0);
}

void	cmd_resolver(t_token **tokens, size_t i, t_linked_env *linked_env)
{
	if (is_built_in(tokens[i]->string))
		return (tokens[i]->token_type = COMMAND_BUILT_IN, (void)0);
	if (cmd_literal_resolver(tokens[i]) != 2)
		return ;
	cmd_path_resolver(tokens[i], linked_env);
}
