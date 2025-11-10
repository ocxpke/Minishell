/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:51:04 by pablo             #+#    #+#             */
/*   Updated: 2025/11/09 16:02:46 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds the "FT_EXIT_ENV=0" environment variable to the environment list.
 *
 * This function creates a key-value pair from the string "FT_EXIT_ENV=0",
 * edits the environment lists to include it, and then frees the allocated
 * key-value array.
 *
 * @param enviroment A pointer to the environment structure to modify.
 * @return The return value from edit_env_lists, indicating success or failure.
 */
static int	add_exit_env(t_envp *enviroment)
{
	int		ret;
	char	*exit_env;
	char	**key_value;

	exit_env = "FT_EXIT_ENV=0";
	key_value = get_key_value(exit_env);
	ret = edit_env_lists(enviroment, key_value);
	return (free_splitted_string(key_value), ret);
}

/**
 * @brief Adds the PID environment variable to the environment list.
 *
 * This function retrieves the process ID (PID) from a file, prepares an
 * environment string using the PID, splits it into key-value pairs, and
 * attempts to add it to the environment lists. It handles memory
 * allocation and deallocation for the retrieved and prepared strings.
 *
 * @param enviroment Pointer to the environment structure where the PID
 *                   variable will be added.
 * @return int Returns the result of the environment list edit operation
 *             (typically 0 on success or an error code on failure).
 *             Returns 0 if any step fails (e.g., unable to get PID,
 *             prepare env string, or split key-value).
 */
static int	add_pid_env(t_envp *enviroment)
{
	int		ret;
	char	*pid_from_file;
	char	*env_prepared;
	char	**key_value;

	pid_from_file = get_pid_from_file();
	if (!pid_from_file)
		return (0);
	env_prepared = get_pid_env(pid_from_file);
	if (!env_prepared)
		return (free(pid_from_file), 0);
	key_value = get_key_value(env_prepared);
	if (!key_value)
		return (free(pid_from_file), free(env_prepared), 0);
	ret = edit_env_lists(enviroment, key_value);
	free_splitted_string(key_value);
	return (free(pid_from_file), free(env_prepared), ret);
}

void	free_env_linked_list(t_linked_env **linked_env)
{
	t_linked_env	*aux;
	t_linked_env	*to_free;

	aux = *linked_env;
	while (aux)
	{
		to_free = aux;
		aux = aux->next;
		free(to_free->key);
		free(to_free->value);
		free(to_free);
	}
	*linked_env = NULL;
}

void	clone_environs(t_envp *enviroment)
{
	int		i;
	char	**key_value;

	i = 0;
	while (environ[i])
	{
		key_value = get_key_value(environ[i]);
		if (key_value)
		{
			check_if_shelllvl(key_value);
			edit_env_lists(enviroment, key_value);
			free_splitted_string(key_value);
		}
		i++;
	}
	enviroment->len_env = i + add_pid_env(enviroment)
		+ add_exit_env(enviroment);
}
