/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/10 18:54:00 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(int *ret)
{
	char	*cwd;

	*ret = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (*ret = -1, perror("Cannot access parent directories"));
	printf("%s\n", cwd);
	free(cwd);
}
