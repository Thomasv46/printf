/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:21:42 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/09 17:44:10 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

t_converter	create_converter(const char **fmt, va_list ap)
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
	converter.pad = get_pad(converter);
	return (converter);
}
