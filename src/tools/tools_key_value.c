/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_key_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:11 by pablo             #+#    #+#             */
/*   Updated: 2025/11/12 21:01:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Validates if a variable name is valid for export.
 *
 * A valid variable name must:
 * - Start with a letter (a-z, A-Z) or underscore (_)
 * - Contain only letters, digits, or underscores
 *
 * @param key The variable name to validate.
 * @return 1 if valid, 0 if invalid.
 */
static int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**get_key_value(char *env)
{
	char	**ret;
	char	*key;
	char	*value;
	int		first_eq;

	if (!env || (env[0] == '='))
		return (NULL);
	ret = (char **)ft_calloc(3, sizeof(char *));
	if (!ret)
		return (perror("Error generating matrix key value\n"), NULL);
	if (!ft_strchr(env, '='))
		return (ret[0] = ft_strdup(env), ret[1] = NULL, ret);
	first_eq = ft_strchr(env, '=') - env;
	key = ft_substr(env, 0, first_eq);
	if (!key || !ft_strlen(key) || !is_valid_identifier(key))
		return (free(key), ft_matrix_free((void ***)&ret, 0), NULL);
	value = ft_strdup(&env[first_eq + 1]);
	ret[0] = key;
	ret[1] = value;
	return (ret);
}
