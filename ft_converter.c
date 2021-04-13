/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:21:42 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/13 09:52:10 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize_data(t_converter *c, int counter)
{
	ft_bzero(c->flags, 6);
	ft_bzero(c->lenght_modifier, 3);
	c->precision = -1;
	c->width = 0;
	c->counter = counter;
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
		&& (!ft_strchr("diuxX", c.convertion) || c.precision < 0))
		return ('0');
	else
		return (' ');
}

t_converter	create_converter(const char **fmt, va_list ap, int counter)
{
	t_converter	c;
	int			i;

	initialize_data(&c, counter);
	i = 0;
	while (ft_strchr("-0# +", **fmt))
		if (!ft_strchr(c.flags, *(*fmt)++))
			c.flags[i++] = *((*fmt) - 1);
	set_data(fmt, ap, &c.width);
	if (c.width < 0)
	{
		if (!ft_strchr(c.flags, '-'))
			c.flags[i] = '-';
		c.width = -c.width;
	}
	if (**fmt == '.')
	{
		(*fmt)++;
		set_data(fmt, ap, &c.precision);
	}
	while (ft_strchr("hl", **fmt))
		c.lenght_modifier[i++] = *(*fmt)++;
	c.convertion = *(*fmt)++;
	c.pad = get_pad(c);
	return (c);
}
