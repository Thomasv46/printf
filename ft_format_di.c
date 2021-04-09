/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:09:55 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/09 15:42:23 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(int n, t_converter c, char *flags, double f_value)
{
	int	i;

	if (!n && !c.precision && c.convertion != 'f')
		return (0);
	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	if (c.precision > i && c.convertion != 'f')
		i = c.precision;
	if (n < 0 || f_value < 0 || ft_strchr(flags, ' ') || ft_strchr(flags, '+'))
		i++;
	return (i);
}

static char	*fill_str(char *s, int n, size_t size)
{
	*(s + size) = 0;
	while (size--)
	{
		if (n < 0)
			*(s + size) = -(n % -10) + '0';
		else
			*(s + size) = n % 10 + '0';
		n /= 10;
	}
	return (s);
}

char	*ft_format_di(va_list ap, t_converter c)
{
	char	*s;
	size_t	size;
	double	f_value;
	int		n;

	f_value = 0;
	if (c.convertion == 'f')
	{
		f_value = va_arg(ap, double);
		n = (int)f_value;
	}
	else
		n = va_arg(ap, int);
	size = get_size(n, c, c.flags, f_value);
	s = malloc(size + 1);
	if (!s)
		return (0);
	s = fill_str(s, n, size);
	if (n < 0 || f_value < 0)
		*s = '-';
	else if (ft_strchr(c.flags, '+'))
		*s = '+';
	else if (ft_strchr(c.flags, ' '))
		*s = ' ';
	return (s);
}
