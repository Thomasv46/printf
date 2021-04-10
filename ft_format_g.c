/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:20:39 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/10 19:46:17 by tvanelst         ###   ########.fr       */
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

char	*ft_format_g(va_list ap, t_converter *c)
{
	int		exponant;
	double	n;
	va_list	ap2;
	char	*s;

	va_copy(ap2, ap);
	n = va_arg(ap, double);
	if (n != n || n == 1.0 / 0.0 || n == -1.0 / 0.0)
		return (handle_edge_cases(n, c));
	exponant = 0;
	if (n)
	{
		while (-1 < n && n < 1)
		{
			exponant--;
			n *= 10;
		}
		while (n / 10 < -1 || 1 < n / 10)
		{
			exponant++;
			n /= 10;
		}
	}
	if (exponant < -4 || exponant > c->precision)
		s = ft_format_e(ap2, c);
	else
		s = ft_format_f(ap2, c);
	va_end(ap2);
	return (s);
}