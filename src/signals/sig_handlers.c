#include "minishell.h"

extern sig_atomic_t signal_recv;

void sigint_handler(int sig){
	(void)sig;

	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

