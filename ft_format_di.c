/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:09:55 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/04 15:06:22 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(int n, int precision, char *flags)
{
	int	i;

	if (!n && !precision)
		return (0);
	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	if (precision > i)
		i = precision;
	if (n < 0 || ft_strchr(flags, ' ') || ft_strchr(flags, '+'))
		i++;
	return (i);
}

char	*ft_format_di(va_list ap, t_converter c)
{
	char	*s;
	size_t	size;
	int		n;
	int		n2;

	if (c.convertion == 'f')
		n = (int)va_arg(ap, double);
	else
		n = va_arg(ap, int);
	n2 = n;
	size = get_size(n, c.precision, c.flags);
	s = malloc(size + 1);
	if (!s)
		return (0);
	*(s + size) = 0;
	while (size-- > 0)
	{
		if (n < 0)
			*(s + size) = -(n % -10) + '0';
		else
			*(s + size) = n % 10 + '0';
		n /= 10;
	}
	if (n2 < 0)
		*s = '-';
	else if (ft_strchr(c.flags, '+'))
		*s = '+';
	else if (ft_strchr(c.flags, ' '))
		*s = ' ';
	return (s);
}
