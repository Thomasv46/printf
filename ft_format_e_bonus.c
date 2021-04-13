/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:56:22 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/13 09:42:48 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_base(t_converter c, ...)
{
	char	*s;
	va_list	ap_base;

	va_start(ap_base, c);
	s = ft_format_f(ap_base, &c);
	va_end(ap_base);
	if (!s)
		return (0);
	return (s);
}

static char	*fill_str2(char *s_int, t_converter c, ...)
{
	char	*s_exp;
	char	*s;
	va_list	ap_exp;
	int		size;

	c.convertion = 'd';
	ft_strlcpy(c.flags, "+", 6);
	c.precision = 2;
	va_start(ap_exp, c);
	s_exp = ft_format_di(ap_exp, &c);
	va_end(ap_exp);
	if (!s_exp)
		return (0);
	size = ft_strlen(s_int) + ft_strlen(s_exp) + 2;
	s = malloc(size);
	if (s)
	{
		ft_strlcpy(s, s_int, size);
		ft_strlcat(s, "e", size);
		ft_strlcat(s, s_exp, size);
	}
	free(s_exp);
	return (s);
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
	va_list	ap2;
	char	*s;
	char	*s_base;
	int		exponent;
	double	n;

	va_copy(ap2, ap);
	n = va_arg(ap, double);
	if (n != n || n == 1.0 / 0.0 || n == -1.0 / 0.0)
		s = ft_format_f(ap2, c);
	else
	{
		get_number_and_exponent(&n, &exponent);
		s_base = get_base(*c, n);
		if (!s_base)
			return (0);
		s = fill_str2(s_base, *c, exponent);
		free(s_base);
	}
	va_end(ap2);
	return (s);
}
