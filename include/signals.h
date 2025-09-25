#include "minishell.h"

#ifndef SIGNALS_H
#define SIGNALS_H

void block_terminal_signals(void);
void sigint_handler(int sig);
void restore_terminal_signals(void);

#endif
