/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:09:55 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/08 16:46:15 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(int n, t_converter c, char *flags)
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
	if (n < 0 || ft_strchr(flags, ' ') || ft_strchr(flags, '+'))
		i++;
	return (i);
}

char	*ft_format_di(va_list ap, t_converter c)
{
	char	*s;
	size_t	size;
	int		n[2];

	if (c.convertion == 'f')
		n[0] = (int)va_arg(ap, double);
	else
		n[0] = va_arg(ap, int);
	n[1] = n[0];
	size = get_size(n[0], c, c.flags);
	s = malloc(size + 1);
	if (!s)
		return (0);
	*(s + size) = 0;
	while (size-- > 0)
	{
		if (n[0] < 0)
			*(s + size) = -(n[0] % -10) + '0';
		else
			*(s + size) = n[0] % 10 + '0';
		n[0] /= 10;
	}
	if (n[1] < 0)
		*s = '-';
	else if (ft_strchr(c.flags, '+'))
		*s = '+';
	else if (ft_strchr(c.flags, ' '))
		*s = ' ';
	return (s);
}
