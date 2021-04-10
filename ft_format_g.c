/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:20:39 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/10 22:49:39 by tvanelst         ###   ########.fr       */
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

static char	*trim_trailing_0(char *s, t_converter *c)
{
	char	*s2;
	int		size;

	if (!ft_strchr(c->flags, '#'))
	{
		s2 = ft_strtrim(s, "0.");
		free(s);
		s = s2;
	}
	else
	{
		size = ft_strlen(s) - 1 ;
		while (*(s + size) == '0')
			size--;
		if (*(s + size) == '.')
			*(s + size + 1) = 0;
	}
	return (s);
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
	{
		c->convertion = 'f';
		s = ft_format_f(ap2, c);
	}
	s = trim_trailing_0(s, c);
	va_end(ap2);
	return (s);
}
/* #include <stdio.h>
int main()
{
	ft_printf(" %#-03.1g ", 1.0);
} */