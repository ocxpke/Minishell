#include "minishell.h"

inline int check_built_in_name(t_shell_data *shell_data)
{
  if (ft_strncmp(shell_data->tokens[0]->string, "exit",
                 ft_strlen(shell_data->tokens[0]->string)) ||
      ft_strncmp(shell_data->tokens[0]->string, "pwd",
                 ft_strlen(shell_data->tokens[0]->string)) ||
      ft_strncmp(shell_data->tokens[0]->string, "cd",
                 ft_strlen(shell_data->tokens[0]->string)) ||
      ft_strncmp(shell_data->tokens[0]->string, "echo",
                 ft_strlen(shell_data->tokens[0]->string)) ||
      ft_strncmp(shell_data->tokens[0]->string, "env",
                 ft_strlen(shell_data->tokens[0]->string)) ||
      ft_strncmp(shell_data->tokens[0]->string, "export",
                 ft_strlen(shell_data->tokens[0]->string)) ||
      ft_strncmp(shell_data->tokens[0]->string, "unset",
                 ft_strlen(shell_data->tokens[0]->string)))
    return (0);
  return (1);
}

char *file_of_piped_command(t_shell_data *shell_data, int index)
{
  char *file_name;

  if (!shell_data->einfo->n_pipes || !check_built_in_name(shell_data))
    return (NULL);
  file_name = generate_cmmd_file_name(index);
  if (!file_name)
    return (0);
  if (!generate_cmmd_file(file_name, shell_data->einfo->commands[index][0]))
    return (free(file_name),  NULL);
  return (file_name);
}

static inline int check_all_built_in(t_shell_data *shell_data, int index)
{
  int ret;

  ret = 0;
  if (!ft_strncmp(shell_data->einfo->commands[index][0], "exit",
                  ft_strlen(shell_data->tokens[0]->string)))
    exit_cmd(shell_data);
  else if (!ft_strncmp(shell_data->einfo->commands[index][0], "pwd",
                       ft_strlen(shell_data->tokens[0]->string)))
    pwd_cmd(&ret);
  else if (!ft_strncmp(shell_data->einfo->commands[index][0], "cd",
                       ft_strlen(shell_data->tokens[0]->string)))
    cd_cmd(shell_data, &ret);
  else if (!ft_strncmp(shell_data->einfo->commands[index][0], "echo",
                       ft_strlen(shell_data->einfo->commands[index][0])))
    echo_cmd(shell_data, &ret);
  else if (!ft_strncmp(shell_data->einfo->commands[index][0], "env",
                       ft_strlen(shell_data->einfo->commands[index][0])))
    env_cmd(&(shell_data->shell_envi), &ret);
  else if (!ft_strncmp(shell_data->einfo->commands[index][0], "export",
                       ft_strlen(shell_data->einfo->commands[index][0])))
    export_cmd(shell_data, &ret);
  else if (!ft_strncmp(shell_data->einfo->commands[index][0], "unset",
                       ft_strlen(shell_data->einfo->commands[index][0])))
    unset_cmd(shell_data, &ret);
  return (0);
}

int check_if_is_built_in(t_shell_data *shell_data, int index)
{
  if (shell_data->einfo->n_pipes)
    return (0);
  return (check_all_built_in(shell_data, index));
}
