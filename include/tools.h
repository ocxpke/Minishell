#include "minishell.h"

#ifndef TOOLS_H
#define TOOLS_H

void clone_environs(t_envp *enviroment);

int add_normal_node(t_linked_env **envp, char **key_value);
int add_ordered_node(t_linked_env **ordered_envp, char **key_value);
int generate_exec_envp(t_envp *shell_envi);

char **get_key_value(char *env);
void free_splitted_string(char **splitted);
int ft_max_len_str(char *str_1, char *str_2);
void free_env_linked_list(t_linked_env **linked_env);
void check_if_shelllvl(char **key_value);
int add_pid_env(t_envp *enviroment);

int add_piped_info_node(t_shell_data *shell_data, int pid, char *file_name);
void free_piped_info_list(t_einfo *einfo);
t_piped_info *get_last_pipe_info_entry(t_shell_data *shell_data);

#endif
