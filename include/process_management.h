#include "minishell.h"

#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H

void	child_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux ,int index);
void	parent_process(t_shell_data *shell_data, int pipes[2], int *pipe_aux, int index);
void execution_cycle(t_shell_data *shell_data);
void exec_subshell(t_shell_data *shell_data, int pipes[2], int *pipe_aux, int index);

#endif
