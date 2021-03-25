/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:44:19 by tvanelst          #+#    #+#             */
/*   Updated: 2021/03/25 14:53:40 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_n_size(double n, int data[3], char *flags)
{
	int	size;
	int n2;

	n2 = n;
	size = 1;
	while (n2 / 10)
	{
		n2 /= 10;
		size++;
	}
	while (n)
	{
		size++;
		n *= 10;
		n2 = n;
		n -= n2;
		printf("%.18f\n", n);
	}
	return (size);
}

char		*ft_format_f(double n, int data[3], char *flags)
{
	int		size;
	char	*s;

	size = get_n_size(n, data, flags);
	s = malloc(size + 1);
	*(s + size--) = 0;
	if (ft_strchr(flags, '#'))
	{
		return (s);
	}
	return (s);
}
