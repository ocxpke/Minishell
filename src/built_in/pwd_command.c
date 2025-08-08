#include "minishell.h"

void pwd_cmd(int *ret){
	char *cwd;

	*ret = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return;
	printf("%s\n", cwd);
	free(cwd);
}
