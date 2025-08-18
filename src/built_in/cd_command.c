#include "minishell.h"

void cd_cmd(t_shell_data *shell_data, int *ret){
	char *home;

	*ret = 1;
	if (!shell_data->tokens[1])
	{
		home = getenv("HOME");
		if (!home)
			printf("HOME not set\n");
		else
			chdir(home);
		return;
	}
	if (shell_data->tokens[2])
		return(printf("Too much arguments\n"), (void)0);
	chdir(shell_data->tokens[1]->string);
}
