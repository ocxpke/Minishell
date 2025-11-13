/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/12 21:01:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(int *ret)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (*ret = -1, perror("Cannot access parent directories"));
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	*ret = 0;
}
