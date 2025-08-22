/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:44:48 by jose-ara          #+#    #+#             */
/*   Updated: 2025/08/01 12:42:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t signal_recv;

static inline void set_func_for_generic_signals(void (*sig_func)(int))
{
	struct sigaction sa;
	int i = 1;

	sa.sa_handler = sig_func;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void block_terminal_signals(void (*set_global_var)(int))
{
	set_func_for_generic_signals(set_global_var);
}

void restore_terminal_signals(){
	set_func_for_generic_signals(SIG_DFL);
}
