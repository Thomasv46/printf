/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanelstlande <thomasvanelstlande@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/19 22:36:15 by thomasvanel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	char_in_str(char c, char *s)
{
	while (*s)
		if (c == *s++)
			return (1);
	return (0);
}

static void	apply_convertion(char convertion, va_list ap, int f_width, int precision, char *flags)
{
	if (convertion == 'c')
		ft_putchar_fd(va_arg(ap, int), 1);
	else if (convertion == 's')
		ft_putstr_fd(va_arg(ap, char *), 1);
	else if (convertion == 'd' || convertion == 'i')
		ft_putnbr_fd(va_arg(ap, int), 1);
	else if (convertion == 'u')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", 1);
	else if (convertion == 'x' || convertion == 'X')
	{
		if (char_in_str('#', flags))
		{
			ft_putchar_fd('0', 1);
			ft_putchar_fd(convertion, 1);
		}
		if (convertion == 'x')
			ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", 1);
		else
			ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", 1);
	}
	if (convertion == 'p')
		return 0;//display adress
}

static const char	*skip_number(char *fmt)
{
	fmt++;
	while (ft_isdigit(fmt))
		fmt++;
	return (fmt);
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int		precision;
	int		f_width;
	char	convertion;
	char	flags[6];
	int		i;

	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt++ == '%')
		{
			ft_bzero(&flags[0], 6);
			i = 0;
			while (char_in_str(*fmt, "-0# +"))
				if (!char_in_str(*fmt, flags))
					*(flags + i++) = *fmt;
			// create copy of ap
			if (ft_isdigit(*fmt))
				f_width = ft_atoi(fmt);
			else if (*fmt == '*')
				f_width = va_arg(ap, int);
			fmt = skip_number(fmt);
			if (*fmt == '.')
			{
				if (ft_isdigit(*++fmt))
					precision = ft_atoi(fmt);
				else if (*fmt == '*')
					precision = va_arg(ap, int);
				fmt = skip_number(fmt);
			}
			convertion = *fmt++;
			apply_convertion(convertion, ap, f_width, precision, &flags);
		}
		else
			ft_putchar_fd(*(fmt - 1), 1);
	}
	va_end(ap);
	return (0);
}

#include <stdio.h>
int main()
{
	printf("bonjour, je %.1s un join\140", "bonjour");
	return 0;
}
