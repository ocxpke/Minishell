#include "minishell.h"

#ifndef BUILT_IN_H
#define BUILT_IN_H

void	exit_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);
void	cd_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);
void	pwd_cmd(int *ret);
void	echo_cmd(t_cinfo *cinfo, int *ret);
void	env_cmd(t_cinfo *cinfo, t_envp *enviroment, int *ret);
int		check_if_is_built_in(t_shell_data *shell_data, t_cinfo *cinfo);
void	print_envi_list(t_linked_env *envp_list, int mode);
void	export_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);
void	unset_cmd(t_shell_data *shell_data, t_cinfo *cinfo, int *ret);
int		check_built_in_name(t_cinfo *cinfo);
int		exec_built_in(t_shell_data *shell_data, t_cinfo *cinfo);

#endif
