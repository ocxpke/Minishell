/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:56:44 by pablo             #+#    #+#             */
/*   Updated: 2025/04/01 18:29:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_perror(char message[], char err_val, char exit_value)
{
	if (err_val > 0)
		errno = err_val;
	perror(message);
	if (exit_value != 0)
		exit(exit_value);
}
