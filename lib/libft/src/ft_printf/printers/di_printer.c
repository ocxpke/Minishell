/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:57:48 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/29 16:35:43 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	di_printer(va_list arg)
{
	char	*str;
	size_t	len;

	str = ft_itoa(va_arg(arg, int));
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	ft_free((void **)&str);
	return (len);
}
