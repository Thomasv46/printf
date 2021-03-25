/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_signed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:09:55 by tvanelst          #+#    #+#             */
/*   Updated: 2021/03/25 09:21:41 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(int n, int data[3], char *flags)
{
	int	i;

	if (!n && !data[1])
		return (0);
	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	if (data[1] > i)
		i = data[1];
	if (n < 0 || ft_strchr(flags, ' ') || ft_strchr(flags, '+'))
		i++;
	return (i);
}

char		*ft_format_di(int n, int data[3], char *flags)
{
	char	*s;
	size_t	size;
	int		n2;

	n2 = n;
	size = get_size(n, data, flags);
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
	else if (ft_strchr(flags, '+'))
		*s = '+';
	else if (ft_strchr(flags, ' '))
		*s = ' ';
	return (s);
}
