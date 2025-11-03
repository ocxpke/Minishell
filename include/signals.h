#include "minishell.h"

#ifndef SIGNALS_H
# define SIGNALS_H

/**
 * @brief Blocks or handles terminal-related signals to prevent interruption.
 *
 * This function configures signal handlers for SIGINT, SIGQUIT, and SIGPIPE.
 *
 * - SIGINT is set to a custom handler (sigint_handler) to manage interrupt
 *   signals, typically allowing graceful handling in a shell environment.
 *
 * - SIGQUIT and SIGPIPE are ignored to prevent the process from terminating
 *   or crashing due to these signals.
 *
 * This is useful to maintain control over signal-driven interruptions and
 * ensure stable execution.
 */
void	block_terminal_signals(void);

/**
 * @brief Restores terminal signals to their default behavior.
 *
 * This function resets the signal handlers for SIGINT (interrupt signal,
 * typically Ctrl+C) and SIGQUIT (quit signal, typically Ctrl+\) to their
 * default actions, allowing the terminal to handle these signals normally
 * without custom handling.
 */
void	restore_terminal_signals(void);

/**
 * @brief Signal handler for SIGINT (interrupt signal).
 *
 * This function is called when a SIGINT signal is received, typically
 * triggered by pressing Ctrl+C. It clears the current input line in
 * readline, moves the cursor to a new line, writes a newline character
 * to stdout, and redisplays the prompt.
 *
 * @param sig The signal number (unused in this implementation).
 */
void	sigint_handler(int sig);



#endif
