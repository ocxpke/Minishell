#include "minishell.h"

inline int	ft_max_len_str(const char *str_1, const char *str_2)
{
	int	len_1;
	int	len_2;

	len_1 = ft_strlen(str_1);
	len_2 = ft_strlen(str_2);
	if (len_1 >= len_2)
		return (len_1);
	return (len_2);
}

void	free_splitted_string(char **splitted)
{
	int	i;

	i = 0;
	if (!splitted)
		return ;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}
