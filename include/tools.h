#include "minishell.h"

#ifndef TOOLS_H
#define TOOLS_H

char **get_key_value(char *env);
void free_splitted_string(char **splitted);
int ft_max_len_str(const char *str_1, const char *str_2);
void check_if_shelllvl(char **key_value);

int	add_piped_info_node(t_shell_data *shell_data, int pid);
void free_piped_info_list(t_einfo *einfo);
t_piped_info *get_last_pipe_info_entry(t_shell_data *shell_data);

#endif
