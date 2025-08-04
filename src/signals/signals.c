/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:44:48 by jose-ara          #+#    #+#             */
/*   Updated: 2025/08/01 12:42:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t signal_recv;

void block_terminal_signals(){
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void restore_terminal_signals(){
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
