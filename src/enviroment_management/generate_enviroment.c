/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_enviroment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:07:16 by pablo             #+#    #+#             */
/*   Updated: 2025/10/29 11:07:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builds a null-terminated environment string in the format
 * "KEY=VALUE".
 *
 * This function constructs an environment variable string from the
 * provided linked environment node. It calculates the total length
 * required for the string (key + "=" + value + null terminator),
 * allocates memory using ft_calloc, and concatenates the key, an
 * equals sign, and the value (if present).
 *
 * @param env_node A pointer to the linked environment node containing
 * the key and value to be used in building the string.
 * @return A pointer to the newly allocated environment string on
 * success, or NULL if memory allocation fails (with an error message
 * printed via perror).
 *
 * @note The returned string must be freed by the caller to avoid
 * memory leaks.
 * @note This is a static function, intended for internal use within
 * the module.
 */
static char	*build_env_string(t_linked_env *env_node)
{
	char	*env;
	size_t	total_len;

	total_len = ft_strlen(env_node->key) + 1 + ft_strlen(env_node->value) + 1;
	env = ft_calloc(1, total_len);
	if (!env)
		return (perror("BOOM in exec_envp"), NULL);
	ft_strlcat(env, env_node->key, total_len);
	ft_strlcat(env, "=", total_len);
	if (env_node->value)
		ft_strlcat(env, env_node->value, total_len);
	return (env);
}

int	generate_exec_envp(t_envp *shell_envi)
{
	t_linked_env	*aux;
	int				i;

	shell_envi->envp_exec = (char **)ft_calloc(shell_envi->len_env + 1,
			sizeof(char *));
	if (!shell_envi->envp_exec)
		return (perror("Error creating envp_exec\n"), 0);
	aux = shell_envi->envp;
	i = 0;
	while (aux && (i <= shell_envi->len_env))
	{
		shell_envi->envp_exec[i] = build_env_string(aux);
		if (!shell_envi->envp_exec[i])
			return (1);
		i++;
		aux = aux->next;
	}
	return (1);
}
