/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:44:19 by tvanelst          #+#    #+#             */
/*   Updated: 2021/03/25 09:45:47 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_n_size(long n, int data[3], char *flags)
{
	int	size;

	size = 1;
	while (n / 10)
	{
		n /= 10;
		size++;
	}
	if (data[1] && data[1 != -1])
		size += data[1];
	else
		size += 7;
	if (ft_strchr(flags, '#') && !data[1])
		size += 1;
	return (size);
}

char	*ft_format_f(long n, int data[3], char *flags)
{
	int		size;
	char	*s;

	size = get_n_size(n, data, flags);
	s = malloc(size + 1);
	*(s + size--) = 0;
	if (data[1 != -1])
		*(s + size - data[1]) = '.';
	if (!n && !data[1])
		*(s + size--) = 0;
	while (size >= 0)
	{
		if (*(s + size) == '.')
			size--;
		*(s + size--) = n % 10;
		n /= 10;
	}
	if (ft_strchr(flags, '#'))
	{
		//display point even without decimal
	}
	return (s);
}
