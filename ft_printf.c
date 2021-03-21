/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/21 13:58:51 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			char_in_str(char c, char *s)
{
	while (*s)
		if (c == *s++)
			return (1);
	return (0);
}

static const char	*set_data(const char *fmt, va_list ap, int *data)
{
	if (ft_isdigit(*fmt))
		*data = (ft_atoi(fmt));
	else if (*fmt == '*')
		*data = (va_arg(ap, int));
	fmt++;
	while (ft_isdigit(*fmt))
		fmt++;
	return (fmt);
}

static void			ft_pad(int *width, char *s, char c, char *flags)
{
	int	size;

	size = ft_strlen(s);
	if (char_in_str('-', flags))
		while ((*width)-- > size)
			ft_putchar_fd(c, 1);
	ft_putstr_fd(s, 1);
	while ((*width)-- > size)
		ft_putchar_fd(c, 1);
}

static void			apply_conversion(char conversion, va_list ap, int data[2], char *flags)
{
	char	*s;

	if (conversion == 'c')
	{
		s = ft_calloc(1, 2);
		*s = va_arg(ap, int);
		ft_pad(&data[0], s, ' ', flags);
		free(s);
	}
	else if (conversion == 's')
		ft_pad(&data[0], va_arg(ap, char *), ' ', flags);
	else if (conversion == 'd' || conversion == 'i')
		ft_putnbr_fd(va_arg(ap, int), 1);
	else if (conversion == 'u')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", 1);
	else if (conversion == 'x' || conversion == 'X')
	{
		if (char_in_str('#', flags))
		{
			ft_putchar_fd('0', 1);
			ft_putchar_fd(conversion, 1);
		}
		if (conversion == 'x')
			ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", 1);
		else
			ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", 1);
	}
	if (conversion == 'p')
		return ;
}

int					ft_printf(const char *fmt, ...)
{
	va_list ap;
	int		data[3];
	char	flags[6];

	va_start(ap, fmt);
	while (*fmt)
		if (*fmt++ == '%')
		{
			ft_bzero(&flags[0], 6);
			ft_bzero(&data[0], sizeof(int) * 3);
			while (char_in_str(*fmt, "-0# +"))
				if (!char_in_str(*fmt++, flags))
					flags[data[2]] = *(fmt - 1);
			fmt = set_data(fmt, ap, &data[0]);
			if (*fmt == '.')
				fmt = set_data(fmt, ap, &data[1]);
			apply_conversion(*fmt++, ap, data, &flags[0]);
		}
		else
			ft_putchar_fd(*(fmt - 1), 1);
	va_end(ap);
	return (0);
}
