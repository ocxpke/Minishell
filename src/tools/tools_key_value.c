/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_key_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:24:11 by pablo             #+#    #+#             */
/*   Updated: 2025/11/10 20:51:54 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!key || !ft_strlen(key))
		return (free(key), ft_matrix_free((void ***)&ret, 0), NULL);
	value = ft_strdup(&env[first_eq + 1]);
	ret[0] = key;
	ret[1] = value;
	return (ret);
}
