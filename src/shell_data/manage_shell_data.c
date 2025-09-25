#include "minishell.h"

extern char** environ;

void free_shell_data(t_shell_data *shell_data)
{
	free_splitted_string(shell_data->shell_envi.envp_exec);
	free_env_linked_list(&(shell_data->shell_envi.envp));
	free_env_linked_list(&(shell_data->shell_envi.ordered_envp));
	clean_entry_info(&(shell_data->einfo));
}

void init_shell_data(t_shell_data *shell_data){
	shell_data->pid_fork = 0;
	shell_data->tokens = NULL;
	shell_data->shell_envi.envp = NULL;
	shell_data->shell_envi.ordered_envp = NULL;
	shell_data->shell_envi.len_env = 0;
	shell_data->shell_envi.envp_exec = NULL;
	shell_data->einfo = NULL;
	clone_environs(&(shell_data->shell_envi));
}
