/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:47 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:00:49 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_cinfo *cinfo, t_envp *enviroment, int *ret)
{
	*ret = 1;
	if (cinfo->array_size > 1)
		return(*ret = -1, errno = EINVAL, perror("bash: env"));
	print_envi_list(enviroment->envp, 1);
}
