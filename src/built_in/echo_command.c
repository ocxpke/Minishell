#include "minishell.h"

void echo_cmd(t_shell_data *shell_data, int *ret){
	int i = 1;

	*ret = 1;
	while(shell_data->tokens[i])
	{
		write(1, shell_data->tokens[i]->string, ft_strlen(shell_data->tokens[i]->string));
		if (shell_data->tokens[i+1])
			write(1, " ", 1);
		i++;
	}
}
