/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_aux_envp_linked_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:03:18 by jose-ara          #+#    #+#             */
/*   Updated: 2025/09/27 19:03:19 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

static int	print_literal(const char *s)
{
	int	cont;

	cont = 2;
	printf("=\"");
	while (*s)
	{
		if (!ft_isprint(*s))
			cont += printf("\\x%02x", (unsigned char)*s);
		else if (*s == '\\')
			cont += printf("\\\\");
		else
			cont += printf("%c", *s);
		s++;
	}
	printf("\"");
	return (cont);
}

void	print_envi_list(t_linked_env *envp_list, int mode)
{
	if (!envp_list)
		return ;
	while (envp_list)
	{
		if (mode)
		{
			printf("%s", envp_list->key);
			if (envp_list->value)
				printf("=%s\n", envp_list->value);
		}
		else
		{
			printf("declare -x %s", envp_list->key);
			if (envp_list->value)
				print_literal(envp_list->value);
			printf("\n");
		}
		envp_list = envp_list->next;
	}
	if (mode)
		printf("%s", RESET);
}
