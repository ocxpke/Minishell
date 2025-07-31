/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_printer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:15:53 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/13 20:24:14 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	s_printer(va_list arg)
{
	char	*str;

	str = (char *)va_arg(arg, int *);
	if (str)
	{
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	else
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
}
