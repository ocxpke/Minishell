#include "minishell.h"

void manage_pipes(int pipes[2], int npipes, int pos)
{
  if (npipes <= 0 || pos == npipes)
    return;
  if (pipe(pipes) == -1)
    return;
}

void execution_cycle(t_shell_data *shell_data) {
  int i = 0;
  int pipes[2];
  int pipe_aux = -1;

  while(i < (shell_data->einfo->n_pipes + 1)){
    manage_pipes(pipes, shell_data->einfo->n_pipes, i);
    if (!check_if_is_built_in(shell_data)) {
      shell_data->pid_fork = fork();
      if (shell_data->pid_fork == -1)
        exit(EXIT_FAILURE);
      if (shell_data->pid_fork == 0)
        child_process(shell_data, pipes, &pipe_aux, i);
      else
        parent_process(shell_data, pipes, &pipe_aux, i);
      //Ver que coño estoy haciendo
    }
    i++;
  }

}
