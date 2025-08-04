#include "minishell.h"

int check_if_is_built_in(t_token **tokens, char **envp) {
	int ret = 0;
  	if (!ft_strncmp(tokens[0]->string, "exit", ft_strlen(tokens[0]->string)))
		exit_cmd(tokens);
	else if (!ft_strncmp(tokens[0]->string, "pwd", ft_strlen(tokens[0]->string)))
		pwd_cmd(tokens, &ret);
	else if (!ft_strncmp(tokens[0]->string, "cd", ft_strlen(tokens[0]->string)))
		cd_cmd(tokens, &ret);
	else if (!ft_strncmp(tokens[0]->string, "echo", ft_strlen(tokens[0]->string)))
		echo_cmd(tokens, &ret);
	else if (!ft_strncmp(tokens[0]->string, "env", ft_strlen(tokens[0]->string)))
		env_cmd(tokens, envp, &ret);
	return (ret);
}
