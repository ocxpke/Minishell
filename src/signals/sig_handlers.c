/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:02:56 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/19 18:03:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_recv;

void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	sigint_heredoc_handler(int sig)
{
	int	fd_null;

	g_signal_recv = sig;
	fd_null = open("/dev/null", O_RDONLY, 0644);
	dup2(fd_null, STDIN_FILENO);
	close(fd_null);
}
