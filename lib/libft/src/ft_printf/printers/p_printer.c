/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_printer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:19:38 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/29 16:35:48 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_printer(va_list arg)
{
	void	*p;
	char	*str;
	size_t	len;

	p = va_arg(arg, void *);
	if (!p)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	str = ft_uintptrtob((uintptr_t)p, "0123456789abcdef");
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str) + 2;
	ft_free((void **)&str);
	return (len);
}
