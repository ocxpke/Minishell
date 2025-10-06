#include "minishell.h"

#ifndef ENVIROMENT_MANAGEMENT_H
#define ENVIROMENT_MANAGEMENT_H

char	*get_enviroment_value(const char *key, t_linked_env *linked_env);
t_linked_env *get_enviroment_node(const char *key, t_linked_env *linked_env);

int edit_env_lists(t_envp *shell_env, char **key_value);

char	*get_pid_from_file(void);
char	*get_pid_env(char *pid);

void	clone_environs(t_envp *enviroment);
int	generate_exec_envp(t_envp *shell_envi);
void	free_env_linked_list(t_linked_env **linked_env);

int	add_normal_node(t_linked_env **envp, char **key_value);
int	add_ordered_node(t_linked_env **ordered_envp, char **key_value);

int modify_value_env_node(t_envp *shell_env, const char *key, char *new_key);

#endif
