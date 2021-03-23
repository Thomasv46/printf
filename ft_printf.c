/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/23 21:20:01 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	output_char(char c, int *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

static void	set_data(const char **fmt, va_list ap, int *data, char *flags)
{
	if (ft_isdigit(**fmt))
		*data = (ft_atoi(*fmt));
	else if (**fmt == '*')
	{
		*data = (va_arg(ap, int));
		(*fmt)++;
	}
	while (ft_isdigit(**fmt))
		(*fmt)++;
	if (**fmt == '.')
	{
		(*fmt)++;
		if (ft_isdigit(**fmt))
			*(data + 1) = ft_atoi(*fmt);
		else if (**fmt == '*')
		{
			*(data + 1) = va_arg(ap, int);
			(*fmt)++;
		}
		else
			*(data + 1) = 0;
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
	if (*data < 0 && !ft_strchr(flags, '-'))
	{
		*data = -*data;
		flags[*(data + 2)] = '-';
	}
}

static void	ft_pad(char conversion, int data[4], char *s, char *flags)
{
	int		size;
	char	c;

	c = ' ';
	size = ft_strlen(s);
	if (!ft_strchr(flags, '-') && data[0] >= 0)
	{
		if (ft_strchr(flags, '0') && (!ft_strchr("diuxX", conversion) || data[1] == -1))
			c = '0';
		if (c == '0' && ft_strchr("-+ ", *s) && ft_strchr("diuxXefg", conversion))
			ft_putchar_fd(*s++, 1);
		if (c == '0' && ((ft_strchr(flags, '#') && ft_strchr("xXefg", conversion)) || ft_strchr("p", conversion)))
		{
			ft_putchar_fd(*s++, 1);
			ft_putchar_fd(*s++, 1);
		}
		while (data[0]-- > size)
			output_char(c, &data[3]);
	}
	ft_putstr_fd(s, 1);
	data[3] += size;
	if (ft_strchr(flags, '-') || data[0] < 0)
		while (data[0]-- > size)
			output_char(c, &data[3]);
}

static void	put_format(char conversion, va_list ap, int data[4], char *flags)
{
	char	*s;

	if (conversion == 'c')
	{
		s = ft_calloc(1, 2);
		s[0] = (unsigned char)va_arg(ap, int);
	}
	else if (conversion == 's')
		s = ft_format_str(va_arg(ap, char *), data[1]);
	else if (ft_strchr("di", conversion))
		s = ft_putnbr_signed(va_arg(ap, int), data, flags);
	else if (ft_strchr("uxX", conversion))
		s = ft_putnbr_base(va_arg(ap, unsigned int), conversion, data, flags);
	if (conversion == 'p')
		s = ft_putnbr_base(va_arg(ap, unsigned long), conversion, data, flags);
	if (ft_strchr("nfge", conversion))
		return ;
	if (conversion == '%')
		s = ft_strdup("%");
	ft_pad(conversion, data, s, flags);
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
	{
		if (*fmt++ == '%')
		{
			ft_bzero(&flags[0], 6);
			ft_bzero(&data[0], sizeof(int) * 3);
			while (ft_strchr("-0# +", *fmt))
				if (!ft_strchr(flags, *fmt++))
					flags[data[2]++] = *(fmt - 1);
			data[1] = -1;
			set_data(&fmt, ap, &data[0], flags);
			put_format(*fmt++, ap, data, &flags[0]);
		}
		else
			output_char(*(fmt - 1), &data[3]);
	}
	va_end(ap);
	return (data[3]);
}
