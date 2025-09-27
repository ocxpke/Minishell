/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:01:28 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:01:28 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(int *ret)
{
	char	*cwd;

	*ret = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	printf("%s\n", cwd);
	free(cwd);
}
