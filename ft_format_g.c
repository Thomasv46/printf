/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:20:39 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/13 10:57:56 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_exponent(double n)
{
	int	exponent;

	exponent = 0;
	if (n)
	{
		while (-1 < n && n < 1)
		{
			(exponent)--;
			n *= 10;
		}
		while (n / 10 < -1 || 1 < n / 10)
		{
			(exponent)++;
			n /= 10;
		}
	}
	return (exponent);
}

static int	get_int_length(double n)
{
	int	i;

	if (!(long long)n)
		return (0);
	i = 1;
	while ((long long)n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*format_str(double n, va_list ap, t_converter *c, char convertion)
{
	int		number_of_decimals;
	int		int_length;

	int_length = get_int_length(n);
	if (!(-1 < n && n < 1))
		number_of_decimals = c->precision;
	else
	{
		number_of_decimals = 0;
		while ((long long)n == 0 && n)
		{
			number_of_decimals++;
			n *= 10;
		}
		number_of_decimals += c->precision - 1;
	}
	if (convertion == 'e')
	{
		c->precision = number_of_decimals - 1;
		return (ft_format_e(ap, c));
	}
	c->precision = number_of_decimals - int_length;
	return (ft_format_f(ap, c));
}

char	*ft_format_g(va_list ap, t_converter *c)
{
	int		exponent;
	double	n;
	va_list	ap2;
	char	*s;

	va_copy(ap2, ap);
	n = va_arg(ap, double);
	if (n != n || n == 1.0 / 0.0 || n == -1.0 / 0.0)
		s = ft_format_f(ap2, c);
	else
	{
		exponent = get_exponent(n);
		if (!c->precision)
			c->precision = 1;
		else if (c->precision < 0)
			c->precision = 6;
		if (exponent < -4 || exponent >= c->precision)
			s = format_str(n, ap2, c, 'e');
		else
			s = format_str(n, ap2, c, 'f');
	}
	va_end(ap2);
	return (s);
}
