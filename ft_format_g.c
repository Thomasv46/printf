/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:20:39 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/11 18:06:02 by tvanelst         ###   ########.fr       */
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

static void trim_trailing_0(char *s, t_converter *c)
{
	int		size;
	char	*s2;
	char	*point;
	int		i;

	point = ft_strchr(s, '.');
	if (point)
	{
		if (c->precision != -1)
		{
			i = 0;
			s2 = point;
			while (ft_isdigit(*++s2))
			{
				if (*s2 != '0' && ++i > c->precision)
				{
					*s2 = 0;
					return ;
				}
			}
		}
		size = ft_strlen(s) - 1 ;
		while (s + size != point && *(s + size) == '0')
			*(s + size--) = 0;
		if (s + size == point && !ft_strchr(c->flags, '#'))
			*(s + size--) = 0;
	}
}

static void	get_number_and_exponent(double *n, int *exponent)
{
	*exponent = 0;
	if (*n)
	{
		while (-1 < *n && *n < 1)
		{
			(*exponent)--;
			*n *= 10;
		}
		while (*n / 10 < -1 || 1 < *n / 10)
		{
			(*exponent)++;
			*n /= 10;
		}
	}
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
		return (handle_edge_cases(n, c));
	get_number_and_exponent(&n, &exponent);
	if (exponent < -4 || (c->precision > 0 && exponent >= c->precision))
		s = ft_format_e(ap2, c);
	else
	{
		if (!n)
			c->precision = 0;
		s = ft_format_f(ap2, c);
		if (n)
			trim_trailing_0(s, c);
	}
	va_end(ap2);
	return (s);
}

/* int main()
{
	ft_printf(" %-02.1g %-02.1g %-02.1g ", 0.0, -1.0, 42.0);
}
 */