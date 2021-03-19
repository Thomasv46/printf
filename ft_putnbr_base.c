/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanelstlande <thomasvanelstlande@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:23:34 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/19 16:25:20 by thomasvanel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	base_index(int i, const char *base)
{
	while (i-- > 0)
		base++;
	return (*base);
}

void		ft_putnbr_base(unsigned int n, const char *base, int fd)
{
	char	c;
	int		base_size;

	base_size = ft_strlen(base);
	if (!n)
		c = base_index(0, base);
	else
	{
		c = base_index(n % base_size, base);
		if (n / base_size)
			ft_putnbr_base(n / base_size, base, fd);
	}
	write(fd, &c, 1);
}
