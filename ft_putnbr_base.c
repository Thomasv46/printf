/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:23:34 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/25 12:57:50 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	base_index(int i, const char *base)
{
	while (i-- > 0)
		base++;
	return (*base);
}

static int	get_n_size(unsigned long n, int data[3], char c, char *flags)
{
	int				size;
	int				base_size;
	unsigned long	n2;

	n2 = n;
	size = 1;
	base_size = data[2];
	while (n / base_size)
	{
		n /= base_size;
		size++;
	}
	if (data[1] > size)
		size = data[1];
	if ((ft_strchr(flags, '#') && c != 'u' && n2) || c == 'p')
		size += 2;
	return (size);
}

static char	*get_base(char c)
{
	if (c == 'u')
		return ("0123456789");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	else
		return ("0123456789abcdef");
}

char		*ft_format_uxp(unsigned long n, char c, int *data, char *flags)
{
	int				size;
	char			*s;
	char			*base;
	unsigned long	n2;

	n2 = n;
	base = get_base(c);
	data[2] = ft_strlen(base);
	size = get_n_size(n, data, c, flags);
	s = malloc(size + 1);
	*(s + size--) = 0;
	if (!n && !data[1])
		*(s + size--) = 0;
	while (size >= 0)
	{
		*(s + size--) = base_index(n % data[2], base);
		n /= data[2];
	}
	if ((ft_strchr(flags, '#') && c != 'u' && n2) || c == 'p')
	{
		if (c == 'p')
			c = 'x';
		*(s + 1) = c;
	}
	return (s);
}
