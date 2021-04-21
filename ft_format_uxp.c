/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_uxp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:23:34 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/21 11:28:36 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	base_index(int i, const char *base)
{
	while (i-- > 0)
		base++;
	return (*base);
}

static int	get_size(unsigned long n, t_converter *c, int base_size)
{
	int				size;
	unsigned long	n2;

	n2 = n;
	size = 1;
	if (!n && !c->precision)
		size = 0;
	while (n / base_size)
	{
		n /= base_size;
		size++;
	}
	if (c->precision > size)
		size = c->precision;
	if ((ft_strchr(c->flags, '#') && c->convertion != 'u' && n2)
		|| c->convertion == 'p')
		size += 2;
	return (size);
}

static char	*set_data(va_list ap, char c, int *base_size, unsigned long *n)
{
	char	*base;

	if (c == 'p')
		*n = va_arg(ap, unsigned long);
	else
		*n = va_arg(ap, unsigned int);
	if (c == 'u')
		base = "0123456789";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	*base_size = ft_strlen(base);
	return (base);
}

static char	*fill_str(unsigned long n, t_converter *c, int size[2], char *base)
{
	char	*s;

	size[0] = get_size(n, c, size[1]);
	s = malloc(size[0] + 1);
	if (!s)
		return (0);
	*(s + size[0]) = 0;
	while (size[0]--)
	{
		*(s + size[0]) = base_index(n % size[1], base);
		n /= size[1];
	}
	return (s);
}

char	*ft_format_uxp(va_list ap, t_converter *c)
{
	int				size[2];
	char			*s;
	char			*base;
	unsigned long	n;

	base = set_data(ap, c->convertion, &size[1], &n);
	s = fill_str(n, c, size, base);
	if (!s)
		return (0);
	if ((ft_strchr(c->flags, '#') && c->convertion != 'u' && n)
		|| c->convertion == 'p')
	{
		if (c->convertion == 'p')
			c->convertion = 'x';
		*(s + 1) = c->convertion;
	}
	return (s);
}
