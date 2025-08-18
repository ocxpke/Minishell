#include "minishell.h"

void execution_cycle(t_shell_data *shell_data) {
  if (!check_if_is_built_in(shell_data)) {
    shell_data->command_exec = get_full_command(shell_data->tokens);
    shell_data->pid_fork = fork();
    if (shell_data->pid_fork == -1)
      exit(EXIT_FAILURE);
    if (shell_data->pid_fork == 0)
      child_process(shell_data);
    else
      parent_process(shell_data);
    free_splitted_string(shell_data->command_exec);
  }
}
