/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:44:06 by pablo             #+#    #+#             */
/*   Updated: 2025/03/22 13:57:33 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(const char *env_var)
{
	extern char	**environ;
	char		**env;
	size_t		len;

	if (!env_var)
		return (NULL);
	len = ft_strlen(env_var);
	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, env_var, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}
