/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:20:39 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/12 17:29:12 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*handle_edge_cases(double n, t_converter *c)
{
	c->pad = ' ';
	if (n == 1.0 / 0)
		return (ft_strdup("inf"));
	else if (n == -1.0 / 0)
		return (ft_strdup("-inf"));
	else
		return (ft_strdup("nan"));
}

static void	get_number_and_exponent(double n, int *exponent)
{
	*exponent = 0;
	if (n)
	{
		while (-1 < n && n < 1)
		{
			(*exponent)--;
			n *= 10;
		}
		while (n / 10 < -1 || 1 < n / 10)
		{
			(*exponent)++;
			n /= 10;
		}
	}
}

static int	get_size(double n, t_converter *c)
{
	int number_of_decimals;
	int	max;

	max = c->precision;
	if (c->precision == -1)
		c->precision = 6;
	else if (!c->precision)
		c->precision = 1;
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
	return (number_of_decimals);
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

char	*ft_format_g(va_list ap, t_converter *c)
{
	int		exponent;
	int		precision;
	double	n;
	va_list	ap2;
	char	*s;

	va_copy(ap2, ap);
	n = va_arg(ap, double);
	if (n != n || n == 1.0 / 0.0 || n == -1.0 / 0.0)
		return (handle_edge_cases(n, c));
	get_number_and_exponent(n, &exponent);
	if (c->precision == 0)
		precision = 1;
	else if (c->precision == -1)
		precision = 6;
	else
		precision = c->precision;
	c->precision = get_size(n, c);
	if (exponent < -4 || exponent >= precision)
	{
		c->precision -= 1;
		s = ft_format_e(ap2, c);
	}
	else
	{
		c->precision -= get_int_length(n);
		s = ft_format_f(ap2, c);
	}

	va_end(ap2);
	return (s);
}
