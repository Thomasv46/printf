/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:44:19 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/09 17:11:42 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_n_size(char *s, int precision)
{
	int	size;

	size = ft_strlen(s);
	if (precision == -1)
		size += 7;
	else if (precision)
		size += precision + 1;
	return (size);
}

static char	*get_int_part(va_list ap, t_converter c, int *int_size, int *size)
{
	char	*s_int;
	char	*s;

	s_int = ft_format_di(ap, c);
	va_end(ap);
	if (!s_int)
		return (0);
	*size = get_n_size(s_int, c.precision);
	s = malloc(*size + 1);
	if (!s)
	{
		free(s_int);
		return (0);
	}
	*(s + *size) = 0;
	*int_size = ft_strlcpy(s, s_int, *size + 1);
	free(s_int);
	return (s);
}

static char	*handle_edge_cases(va_list ap, double n)
{
	va_end(ap);
	if (n == 1.0 / 0.0)
		return (ft_strdup("inf"));
	else if (n == -1.0 / 0.0)
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

char	*ft_format_f(va_list ap, t_converter converter)
{
	int		size;
	int		int_size;
	char	*s;
	double	n;
	va_list	ap2;

	va_copy(ap2, ap);
	n = va_arg(ap, double);
	if (n != n || n == 1.0 / 0.0 || n == -1.0 / 0.0)
		return (handle_edge_cases(ap2, n));
	s = get_int_part(ap2, converter, &int_size, &size);
	if (!s)
		return (0);
	n = n - (int)n;
	if (n < 0)
		n *= -1;
	if (converter.precision || ft_strchr(converter.flags, '#'))
		*(s + int_size++) = '.';
	while (int_size < size)
	{
		n = (n - (int)n) * 10;
		*(s + int_size++) = (int)n % 10 + '0';
	}
	return (get_rounded_value(n - (int)n, int_size, s));
}
