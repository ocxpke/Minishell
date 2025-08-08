#include "minishell.h"

/**
 * @note se puede declarar una varibale rollo SET=algo, eso debemos controlarlo??
 * @note arreglar --> tiene que coger el string + grande
 */

int check_if_is_built_in(t_shell_data *shell_data) {
	int ret = 0;
  	if (!ft_strncmp(shell_data->tokens[0]->string, "exit", ft_strlen(shell_data->tokens[0]->string)))
		exit_cmd(shell_data);
	else if (!ft_strncmp(shell_data->tokens[0]->string, "pwd", ft_strlen(shell_data->tokens[0]->string)))
		pwd_cmd(&ret);
	else if (!ft_strncmp(shell_data->tokens[0]->string, "cd", ft_strlen(shell_data->tokens[0]->string)))
		cd_cmd(shell_data, &ret);
	else if (!ft_strncmp(shell_data->tokens[0]->string, "echo", ft_strlen(shell_data->tokens[0]->string)))
		echo_cmd(shell_data, &ret);
	else if (!ft_strncmp(shell_data->tokens[0]->string, "env", ft_strlen(shell_data->tokens[0]->string)))
		env_cmd(&(shell_data->shell_envi), &ret);
	else if (!ft_strncmp(shell_data->tokens[0]->string, "export", ft_strlen(shell_data->tokens[0]->string)))
		export_cmd(shell_data, &ret);
	else if (!ft_strncmp(shell_data->tokens[0]->string, "unset", ft_strlen(shell_data->tokens[0]->string)))
		unset_cmd(shell_data, &ret);
	return (ret);
}
