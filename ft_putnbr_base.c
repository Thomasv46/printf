/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:23:34 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/21 22:25:35 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	base_index(int i, const char *base)
{
	while (i-- > 0)
		base++;
	return (*base);
}

static int	get_n_size(unsigned long n, const char *base, char c, char *flags)
{
	int	size;
	int	base_size;

	size = 0;
	base_size = ft_strlen(base);
	while (n)
	{
		n /= base_size;
		size++;
	}
	if ((ft_strchr(flags, '#') && c != 'u') || c == 'p')
		size += 2;
	return (size);
}

static char	*get_base(char c)
{
	char *s;

	s = 0;
	if (c == 'u')
		s = "0123456789";
	else if (c == 'x' || c == 'p')
		s = "0123456789abcdef";
	else if (c == 'X')
		s = "0123456789ABCDEF";
	return (s);
}

char		*ft_putnbr_base(unsigned long n, char c, char *flags)
{
	int		base_size;
	int		size;
	char	*s;
	char	*base;

	base = get_base(c);
	size = get_n_size(n, base, c, flags);
	s = malloc(size + 1);
	base_size = ft_strlen(base);
	*(s + size--) = 0;
	if (!n)
		*(s + size--) = base_index(0, base);
	while (n)
	{
		*(s + size--) = base_index(n % base_size, base);
		n /= base_size;
	}
	if (ft_strchr(flags, '#') || c == 'p')
	{
		if (c == 'p')
			c = 'x';
		*(s + size--) = c;
		*(s + size--) = '0';
	}
	return (s);
}
