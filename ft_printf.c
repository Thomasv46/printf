/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/25 13:35:30 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	output_char(char c, int *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

static void	get_data(const char **fmt, va_list ap, int *data, char *flags)
{
	if (**fmt == '*')
	{
		*data = va_arg(ap, int);
		(*fmt)++;
	}
	else
		*data = ft_atoi(*fmt);
	while (ft_isdigit(**fmt))
		(*fmt)++;
	if (**fmt == '.' && flags)
	{
		(*fmt)++;
		get_data(fmt, ap, data + 1, 0);
	}
	if (data[0] < 0 && flags)
	{
		if (!ft_strchr(flags, '-'))
			flags[data[2]] = '-';
		data[0] = -data[0];
	}
}

static void	ft_pad(char c, int data[4], char *s, char *flags)
{
	char	pad;

	pad = ' ';
	if (!ft_strchr(flags, '-'))
	{
		if (ft_strchr(flags, '0') && (!ft_strchr("diuxX", c) || data[1] == -1))
			pad = '0';
		if (pad == '0' && ft_strchr("-+ ", *s) && ft_strchr("diuxXefg", c))
			ft_putchar_fd(*s++, 1);
		if (pad == '0' && ((ft_strchr(flags, '#') && ft_strchr("xXefg", c)) || c == 'p'))
		{
			ft_putchar_fd(*s++, 1);
			ft_putchar_fd(*s++, 1);
		}
		while (data[0]-- > data[2])
			output_char(pad, &data[3]);
	}
	data[3] += data[2];
	if (c == 'c' && !*s)
		ft_putchar_fd(*s, 1);
	else
		ft_putstr_fd(s, 1);
	while (data[0]-- > data[2])
		output_char(pad, &data[3]);
}

static void	put_format(char c, va_list ap, int data[4], char *flags)
{
	char	*s;

	if (c == 'c')
		s = ft_format_c((unsigned char)va_arg(ap, int));
	else if (c == 's')
		s = ft_format_s(va_arg(ap, char *), data[1]);
	else if (ft_strchr("di", c))
		s = ft_format_di(va_arg(ap, int), data, flags);
	else if (ft_strchr("uxX", c))
		s = ft_format_uxp(va_arg(ap, unsigned int), c, data, flags);
	else if (c == 'p')
		s = ft_format_uxp(va_arg(ap, unsigned long), c, data, flags);
	else if (ft_strchr("nfge", c))
		return ;
	else
		s = ft_format_c(c);
	data[2] = ft_strlen(s);
	if (c == 'c')
		data[2] = 1;
	ft_pad(c, data, s, flags);
	free(s);
}

int			ft_printf(const char *fmt, ...)
{
	va_list ap;
	int		data[4];
	char	flags[6];

	va_start(ap, fmt);
	data[3] = 0;
	while (*fmt)
		if (*fmt++ == '%')
		{
			ft_bzero(&flags[0], 6);
			ft_bzero(&data[0], sizeof(int) * 3);
			while (ft_strchr("-0# +", *fmt))
				if (!ft_strchr(flags, *fmt++))
					flags[data[2]++] = *(fmt - 1);
			data[1] = -1;
			get_data(&fmt, ap, data, flags);
			put_format(*fmt++, ap, data, &flags[0]);
		}
		else
			output_char(*(fmt - 1), &data[3]);
	va_end(ap);
	return (data[3]);
}
