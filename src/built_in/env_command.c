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
	//TODO: check correct num of cmd_args
	if (ft_matrix_len((void **) cinfo->cmd_and_args) > 1)
		return(errno = EINVAL, perror("Too many arguments\n"));
	print_envi_list(enviroment->envp, 1);
}
