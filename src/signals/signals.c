/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:44:48 by jose-ara          #+#    #+#             */
/*   Updated: 2025/07/31 15:47:12 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Changes default action for terminal related signals
 **/
void	terminal_signals(void (*func)(int))
{
	signal(SIGINT, func);  /* crtl+c Interrupt from keyboard */
	signal(SIGQUIT, func); /* ctrl+\ Quit from keyboard */
	signal(SIGTSTP, func); /* crtl+z Stop typed at keyboard */
	signal(SIGTTIN, func); /* Background process tries terminal input */
	signal(SIGTTOU, func); /* Background process tries terminal output */
}

/**
 * Blocks or masks a signal.
 * The signal handler execution for the signal is deferred until the signal
 * is unblocked.
 * If several instances of the signal ocurred after being blocked, when
 * unblocked, the handler for that signal executes only once.
 **/
void	block_signal(int signal, int block)
{
	sigset_t	block_sigchld;

	/* Declare and initialize signal masks */
	sigemptyset(&block_sigchld);
	sigaddset(&block_sigchld, signal);
	if (block)
	{
		/* Blocks signal */
		sigprocmask(SIG_BLOCK, &block_sigchld, NULL);
	}
	else
	{
		/* Unblocks signal */
		sigprocmask(SIG_UNBLOCK, &block_sigchld, NULL);
	}
}
