#include "minishell.h"
#include "colors.h"

extern sig_atomic_t signal_recv;

/**
 * @note cortarme los cojones con las funciones async-safe pa los
 * handlers
 */

void sigint_handler(){
	fflush(stdout);
	rl_replace_line("", 0);
	printf("%sMinishell%s@%s%s%s", YELLOW, RED , BLUE, getenv("USER"), RESET);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
	signal_recv = 0;
}

void sig_setter(int sig){
	signal_recv = sig;
	if (sig == SIGINT)
		write(STDIN_FILENO, "\0\n", 2);
}
