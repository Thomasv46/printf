/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:23:34 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/21 15:21:30 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	base_index(int i, const char *base)
{
	while (i-- > 0)
		base++;
	return (*base);
}

static int	get_n_size(unsigned int n, const char	*base)
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
	return (size);
}

char		*ft_putnbr_base(unsigned int n, const char *base)
{
	int		base_size;
	int		size;
	char	*s;

	size = get_n_size(n, base);
	s = malloc(size + 1);
	base_size = ft_strlen(base);
	*(s + size--) = 0;
	if (!n)
		*s = base_index(0, base);
	while (n)
	{
		*(s + size--) = base_index(n % base_size, base);
		n /= base_size;
	}
	return (s);
}
