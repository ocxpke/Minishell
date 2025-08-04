#include "minishell.h"

void cd_cmd(t_token **tokens, int *ret){
	*ret = 1;
	chdir(tokens[1]->string);
}

void pwd_cmd(t_token **tokens, int *ret){
	char *cwd;

	*ret = 1;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return(write(2, "getcwd error\n", 14), (void)0);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
}

void echo_cmd(t_token **tokens, int *ret){
	int i = 1;

	*ret = 1;
	while(tokens[i])
	{
		write(1, tokens[i]->string, ft_strlen(tokens[i]->string));
		if (tokens[i+1])
			write(1, " ", 1);
		i++;
	}
}

//Arreglar saca un "=(null)", hay que borralo
void env_cmd(t_token **tokens, char **envp, int *ret){
	int i = 0;
	char *env_desc;

	*ret = 1;
	if (!envp)
		return;
	while(envp[i]){
		env_desc = getenv(envp[i]);
		printf("%d --> %s=%s\n", i, envp[i], env_desc);
		//Se libera esto??? en el manual no sale na
		free(env_desc);
		i++;
	}
}

void exit_cmd(t_token **tokens){
	rl_clear_history();
	free_tokens(tokens);
	exit(EXIT_SUCCESS);
}
