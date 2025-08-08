#include "minishell.h"

void cd_cmd(t_shell_data *shell_data, int *ret){
	*ret = 1;
	if (!shell_data->tokens[1] || shell_data->tokens[2])
		return;
	chdir(shell_data->tokens[1]->string);
}
