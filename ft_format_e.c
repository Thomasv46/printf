/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:56:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/12 18:39:06 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*fill_str1(t_converter c, ...)
{
	char	*s;
	va_list	ap_exp;

	va_start(ap_exp, c);
	s = ft_format_f(ap_exp, &c);
	va_end(ap_exp);
	if (!s)
		return (0);
	return (s);
}

static char	*fill_str2(char *s_int, t_converter c, ...)
{
	char	*s;
	char	*s_main;
	va_list	ap_int;
	int		size;

	c.convertion = 'd';
	ft_strlcpy(c.flags, "+0", 6);
	c.precision = 2;
	va_start(ap_int, c);
	s = ft_format_di(ap_int, &c);
	va_end(ap_int);
	if (!s)
		return (0);
	size = ft_strlen(s_int) + ft_strlen(s) + 1;
	s_main = malloc(size + 1);
	if (s_main)
	{
		ft_strlcpy(s_main, s_int, size - 3);
		ft_strlcat(s_main, "e", size + 1);
		ft_strlcat(s_main, s, size + 1);
	}
	free(s);
	return (s_main);
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

char	*ft_format_e(va_list ap, t_converter *c)
{
	int		exponent;
	va_list	ap2;
	char	*s_int;
	char	*s2;
	double	n;

	va_copy(ap2, ap);
	n = va_arg(ap, double);
	if (n != n || n == 1.0 / 0.0 || n == -1.0 / 0.0)
		s2 = ft_format_f(ap2, c);
	else
	{
		get_number_and_exponent(&n, &exponent);
		s_int = fill_str1(*c, n);
		if (!s_int)
			return (0);
		s2 = fill_str2(s_int, *c, exponent);
		free(s_int);
	}
	va_end(ap2);
	return (s2);
}
