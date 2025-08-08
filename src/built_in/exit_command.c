#include "minishell.h"

void exit_cmd(t_shell_data *shell_data){
	rl_clear_history();
	free_shell_data(shell_data);
	exit(EXIT_SUCCESS);
}
