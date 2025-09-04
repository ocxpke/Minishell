#include "minishell.h"
#include "colors.h"

inline int ft_max_len_str(char *str_1, char *str_2){
	int len_1;
	int len_2;

	len_1 = ft_strlen(str_1);
	len_2 = ft_strlen(str_2);
	if (len_1 >= len_2)
		return (len_1);
	return(len_2);
}

static int print_literal(const char *s) {
	int cont = 0;
    while (*s) {
        if (!ft_isprint(*s))
            cont += printf("\\x%02x", (unsigned char)*s);
        else if (*s == '\\')
        	cont +=printf("\\\\");
        else
        	cont +=printf("%c", *s);
        s++;
    }
	return (cont);
}

void print_envi_list(t_linked_env *envp_list, int mode)
{
	if (!envp_list)
		return;
	while(envp_list){
		if (mode)
		{
			printf("%s", envp_list->key);
			if (envp_list->value)
				printf("=%s\n", envp_list->value);
		}
		else
		{
			printf("declare -x %s", envp_list->key);
			/**
			 * @note Este if es de las cosas mas gitanas que he hecho en mi vida
			 */
			if (envp_list->value && printf("=\"") && print_literal(envp_list->value))
				printf("\"");
			printf("\n");
		}
		envp_list = envp_list->next;
	}
	if (mode)
		printf("%s", RESET);
}
