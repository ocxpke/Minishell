/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:47 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/10 18:49:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_cinfo *cinfo, t_envp *enviroment, int *ret)
{
	*ret = 1;
	if (cinfo->array_size > 1)
		return (*ret = -1, errno = EINVAL, perror("bash: env"));
	print_envi_list(enviroment->envp, 1);
}
