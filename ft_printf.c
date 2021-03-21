/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/21 18:43:58 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_data(const char **fmt, va_list ap, int *data)
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
}

static void	ft_pad(char conversion, int data[2], char *s, char *flags)
{
	int		size;
	char	c;

	c = ' ';
	size = ft_strlen(s);
	if (!ft_strchr(flags, '-'))
	{
		if (ft_strchr(flags, '0') && ft_strchr("diuxXefg", conversion)
			&& (!ft_strchr("diuxX", conversion) || !data[1]))
			c = '0';
		while (data[0]-- > size)
			ft_putchar_fd(c, 1);
	}
	ft_putstr_fd(s, 1);
	if (ft_strchr(flags, '-'))
		while (data[0]-- > size)
			ft_putchar_fd(c, 1);
}

static void	put_format(char conversion, va_list ap, int data[2], char *flags)
{
	char	*s;

	if (conversion == 'c')
	{
		s = ft_calloc(1, 2);
		s[0] = va_arg(ap, int);
	}
	else if (conversion == 's')
		s = ft_strdup(va_arg(ap, char *));
	else if (ft_strchr("di", conversion))
		s = ft_itoa(va_arg(ap, int));
	else if (conversion == 'u')
		s = ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", conversion, flags);
	else if (conversion == 'x')
		s = ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", conversion, flags);
	else if (conversion == 'X')
		s = ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", conversion, flags);
	if (conversion == 'p')
		s = ft_putnbr_base(va_arg(ap, unsigned long), "0123456789abcdef", conversion, flags);
	ft_pad(conversion, data, s, flags);
	free(s);
}

int			ft_printf(const char *fmt, ...)
{
	va_list ap;
	int		data[3];
	char	flags[6];

	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt++ == '%')
		{
			ft_bzero(&flags[0], 6);
			ft_bzero(&data[0], sizeof(int) * 3);
			while (ft_strchr("-0# +", *fmt))
				if (!ft_strchr(flags, *fmt++))
					flags[data[2]] = *(fmt - 1);
			set_data(&fmt, ap, &data[0]);
			if (*fmt == '.')
				set_data(&fmt, ap, &data[1]);
			put_format(*fmt++, ap, data, &flags[0]);
		}
		else
			ft_putchar_fd(*(fmt - 1), 1);
	}
	va_end(ap);
	return (0);
}

int			main(void)
{
	char	*str = malloc(1);
	ft_printf("%-15s-%10c\n%010X\n%p", "bonjour", 't', 5499, str);
	write(1, "\n", 1);
	printf("%-15s-%10c\n%010X\n%p", "bonjour", 't', 5499, str);
}
