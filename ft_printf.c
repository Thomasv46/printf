/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/03 23:59:05 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	output_char(char c, int *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

static void	set_data(const char **fmt, va_list ap, int *data)
{
	if (**fmt == '*')
		*data = va_arg(ap, int);
	else if (*data && ft_atoi(*fmt) < 0)
		*data = 0;
	else
		*data = ft_atoi(*fmt);
	while (ft_isdigit(**fmt) || **fmt == '*')
		(*fmt)++;
}

static t_converter	create_converter(const char **fmt, va_list ap)
{
	t_converter	converter;
	int			i;

	ft_bzero(converter.flags, 6);
	converter.precision = -1;
	converter.width = 0;
	i = 0;
	while (ft_strchr("-0# +", **fmt))
		if (!ft_strchr(converter.flags, *(*fmt)++))
			converter.flags[i++] = *((*fmt) - 1);
	set_data(fmt, ap, &converter.width);
	if (converter.width < 0)
	{
		if (!ft_strchr(converter.flags, '-'))
			converter.flags[i] = '-';
		converter.width = -converter.width;
	}
	if (**fmt == '.')
	{
		(*fmt)++;
		set_data(fmt, ap, &converter.precision);
	}
	converter.convertion = *(*fmt)++;
	return (converter);
}

static void	ft_pad(t_converter c, char *s, int *counter, int len)
{
	char	pad;

	pad = ' ';
	if (!ft_strchr(c.flags, '-'))
	{
		if (ft_strchr(c.flags, '0') && (!ft_strchr("diuxX", c.convertion) || c.precision == -1))
		{
			pad = '0';
			if (s && ft_strchr("-+ ", *s) && ft_strchr("diuxXefg", c.convertion))
				ft_putchar_fd(*s++, 1);
		}
		if (s && pad == '0' && (c.convertion == 'p'
				|| (ft_strchr(c.flags, '#') && ft_strchr("xXefg", c.convertion))))
		{
			ft_putchar_fd(*s++, 1);
			ft_putchar_fd(*s++, 1);
		}
		while (c.width-- > len)
			output_char(pad, counter);
	}
	*counter += len;
	if (c.convertion == 'c' && s && !*s)
		ft_putchar_fd(*s, 1);
	else if (s)
		ft_putstr_fd(s, 1);
	while (c.width-- > len)
		output_char(pad, counter);
}

static char	*convert_to_str(va_list ap, t_converter c)
{
	t_tuple	funptr[4];
	int		i;

	funptr[0].func = &ft_format_s;
	funptr[0].str = "s";
	funptr[1].func = &ft_format_di;
	funptr[1].str = "di";
	funptr[2].func = &ft_format_uxp;
	funptr[2].str = "uxXp";
	funptr[3].func = &ft_format_c;
	funptr[3].str = "c";
	i = 0;
	while (!ft_strchr(funptr[i].str, c.convertion) && i < 3)
		i++;
	return (funptr[i].func(ap, c));
}

static void	display_value(va_list ap, const char **fmt, int *counter)
{
	char		*s;
	int			len;
	t_converter	c;

	c = create_converter(fmt, ap);
	if (ft_strchr("nfge", c.convertion) || !c.convertion)
		return ;
	s = convert_to_str(ap, c);
	if (s)
		len = ft_strlen(s);
	if (c.convertion == 'c')
		len = 1;
	ft_pad(c, s, counter, len);
	if (s)
		free(s);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	int			counter;

	va_start(ap, fmt);
	counter = 0;
	while (*fmt)
	{
		if (*fmt++ != '%')
			output_char(*(fmt - 1), &counter);
		else if (*fmt)
			display_value(ap, &fmt, &counter);
	}
	va_end(ap);
	return (counter);
}
