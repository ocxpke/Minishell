#include "minishell.h"

char *generate_cmmd_file_name(int index)
{
	char *ret;
	char *num;
	int len;

	num = ft_itoa(index);
	if (!num)
		return (NULL);
	len = ft_strlen("piped_file") + ft_strlen(num) + 1;
	ret = (char *) ft_calloc(len, sizeof(char));
	if (!ret)
		return (free(num), NULL);
	ft_strlcat(ret, "piped_file", len);
	ft_strlcat(ret, num, len);
	return (free(num), ret);
}

int generate_cmmd_file(char *file_name, char *cmmd_to_write)
{
	int fd_cmmd;

	fd_cmmd = open(file_name, O_WRONLY | O_CREAT, 0664);
	if (fd_cmmd == -1)
		return  (0);
	write(fd_cmmd, cmmd_to_write, ft_strlen(cmmd_to_write));
	close(fd_cmmd);
	return (0);
}
