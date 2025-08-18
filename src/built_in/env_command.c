#include "minishell.h"

void env_cmd(t_envp *enviroment, int *ret){
	*ret = 1;
	print_envi_list(enviroment->envp, 1);
}
