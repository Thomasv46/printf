/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanelstlande <thomasvanelstlande@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/18 14:34:33 by thomasvanel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int		d;
	char	c;
	char	*s;

	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == 'c')
				ft_putchar_fd(va_arg(ap, int), 1);
			if (*fmt == 's')
				ft_putstr_fd(va_arg(ap, char *), 1);
			if (*fmt == 'd' || *fmt == 'i')
				ft_putnbr_fd(va_arg(ap, int), 1);
			if (*fmt == 'u')
				ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", 1);
			if (*fmt == 'x' || *fmt == 'X')
				ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", 1);
		}
		else
			ft_putchar(*fmt);
	}
	va_end(ap);
	return (0);
}