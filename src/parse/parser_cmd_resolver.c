/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_resolver.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:08:16 by pablo             #+#    #+#             */
/*   Updated: 2025/07/30 21:54:24 by pablo            ###   ########.fr       */
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

void	cmd_resolver(t_token **tokens, size_t i)
{
	char	*cmd_path;
	char	*tmp;
	char	**paths;
	char	*env_path;

	if (is_built_in(tokens[i]->string))
		return (tokens[i]->token_type = UNDEFINED, (void)0);
	tokens[i]->token_type = COMMAND_ROUTE;
	if (ft_strchr(tokens[i]->string, '/') != NULL)
		return ;
	env_path = getenv("PATH");
	if (!env_path)
		return (tokens[i]->token_type = UNDEFINED, (void)0);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (tokens[i]->token_type = UNDEFINED, (void)0);
	cmd_path = search_path(paths, tokens[i]->string);
	ft_matrix_free((void **)paths, 0);
	if (cmd_path)
		return (tmp = tokens[i]->string, tokens[i]->string = cmd_path,
			free(tmp), (void)0);
	else
		tokens[i]->token_type = UNDEFINED;
}
