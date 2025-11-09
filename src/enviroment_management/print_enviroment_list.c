/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_enviroment_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:03:18 by jose-ara          #+#    #+#             */
/*   Updated: 2025/11/09 16:02:58 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

/**
 * @brief Prints a string with literal representation, escaping
 * non-printable characters and backslashes.
 *
 * This function iterates through the input string and prints each
 * character. Non-printable characters are printed in hexadecimal
 * escape sequence format (e.g., \x00). Backslashes are escaped as
 * double backslashes (\\). Printable characters are printed as-is.
 *
 * @param s The null-terminated string to be printed.
 * @return The total number of characters printed.
 */
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

// TODO: Esta función está dentro de enviroment_management pero se declara en
// built_in.h

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
