/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:44:19 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/10 18:10:43 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_n_size(char *s, t_converter *c)
{
	int	size;

	size = ft_strlen(s);
	if (c->precision == -1)
		size += 7;
	else if (c->precision)
		size += c->precision + 1;
	else if (!c->precision && ft_strchr(c->flags, '#'))
		size += 1;
	return (size);
}

static char	*get_int_part(t_converter *c, int *size, ...)
{
	char	*s_int;
	char	*s;
	va_list	ap;

	va_start(ap, size);
	s_int = ft_format_di(ap, c);
	va_end(ap);
	if (!s_int)
		return (0);
	*size = get_n_size(s_int, c);
	s = malloc(*size + 1);
	if (!s)
	{
		free(s_int);
		return (0);
	}
	*(s + *size) = 0;
	*(size + 1) = ft_strlcpy(s, s_int, *size + 1);
	free(s_int);
	return (s);
}

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

static char	*get_rounded_value(double n, int int_size, char *s)
{
	if ((n * 10) == 5)
		*(s + int_size - 1) += (*(s + int_size - 1) - '0') % 2;
	else if ((n * 10) > 5)
	{
		while (*(s + int_size - 1) == '9')
			*(s + int_size-- - 1) = '0';
		*(s + int_size - 1) += 1;
	}
	return (s);
}

char	*ft_format_f(va_list ap, t_converter *c)
{
	int		size[2];
	char	*s;
	double	n;

	n = va_arg(ap, double);
	if (n != n || n == 1.0 / 0.0 || n == -1.0 / 0.0)
		return (handle_edge_cases(n, c));
	s = get_int_part(c, size, n);
	if (!s)
		return (0);
	if (n > 0 && (long long)n < 0)
		n += (long long)n;
	n = n - (long long)n;
	if (n < 0)
		n *= -1;
	if (c->precision || ft_strchr(c->flags, '#'))
		*(s + size[1]++) = '.';
	while (size[1] < size[0])
	{
		n = (n - (long long)n) * 10;
		*(s + size[1]++) = (long long)n % 10 + '0';
	}
	return (get_rounded_value(n - (long long)n, size[1], s));
}
