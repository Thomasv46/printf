/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:21:42 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/10 11:56:53 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize_data(t_converter *converter, int counter)
{
	ft_bzero(converter->flags, 6);
	ft_bzero(converter->lenght_modifier, 3);
	converter->precision = -1;
	converter->width = 0;
	converter->counter = counter;
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

static char	get_pad(t_converter c)
{
	if (!ft_strchr(c.flags, '-') && ft_strchr(c.flags, '0')
		&& (!ft_strchr("diuxX", c.convertion) || c.precision == -1))
		return ('0');
	else
		return (' ');
}

t_converter	create_converter(const char **fmt, va_list ap, int counter)
{
	t_converter	converter;
	int			i;

	initialize_data(&converter, counter);
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
	while (ft_strchr("hl", **fmt))
		converter.lenght_modifier[i++] = *(*fmt)++;
	converter.convertion = *(*fmt)++;
	converter.pad = get_pad(converter);
	return (converter);
}
