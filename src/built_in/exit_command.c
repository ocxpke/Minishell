/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:00:52 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:00:53 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_shell_data *shell_data)
{
	rl_clear_history();
	free_shell_data(shell_data);
	exit(EXIT_SUCCESS);
}
