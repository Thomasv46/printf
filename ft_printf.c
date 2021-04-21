/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:25:42 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/21 11:25:03 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	output_char(char c, int *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

static char	*convert_arg_to_str(va_list ap, t_converter *c)
{
	t_tuple		*funptr;
	int			i;

	funptr = (t_tuple[]){{"s", &ft_format_s}, {"di", &ft_format_di},
	{"uxXp", &ft_format_uxp}, {"n", &ft_format_n}, {"f", &ft_format_f},
	{"e", &ft_format_e}, {"g", &ft_format_g}, {"c", &ft_format_c}};
	i = 0;
	while (!ft_strchr(funptr[i].str, c->convertion) && i < 7)
		i++;
	return (funptr[i].func(ap, c));
}

static void	display_formated_arg(t_converter c, char *s, int *counter, int len)
{
	if (!ft_strchr(c.flags, '-'))
	{
		if (s && c.pad == '0')
		{
			if (ft_strchr("-+ ", *s) && !ft_strchr("cs", c.convertion))
				ft_putchar_fd(*s++, 1);
			if (ft_strchr("pxX", c.convertion) && s[1] && ft_strchr("xX", s[1]))
			{
				ft_putchar_fd(*s++, 1);
				ft_putchar_fd(*s++, 1);
			}
		}
		while (c.width-- > len)
			output_char(c.pad, counter);
	}
	if (c.convertion == 'c' && s && !*s)
		ft_putchar_fd(*s, 1);
	else if (s)
		ft_putstr_fd(s, 1);
	while (c.width-- > len)
		output_char(c.pad, counter);
}

static void	process_argument(va_list ap, const char **fmt, int *counter)
{
	char		*s;
	int			len;
	t_converter	c;

	c = create_converter(fmt, ap, *counter);
	if (c.convertion)
		s = convert_arg_to_str(ap, &c);
	if (c.convertion == 'n' || !c.convertion)
		return ;
	len = 1;
	if (s && c.convertion != 'c')
		len = ft_strlen(s);
	display_formated_arg(c, s, counter, len);
	*counter += len;
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
			process_argument(ap, &fmt, &counter);
	}
	va_end(ap);
	return (counter);
}
