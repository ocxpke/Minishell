/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_printer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:57:48 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/29 16:35:50 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	u_printer(va_list arg)
{
	char			*str;
	unsigned int	un;
	size_t			len;

	un = (unsigned int)va_arg(arg, int);
	str = ft_uitoa(un);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	ft_free((void **)&str);
	return (len);
}
