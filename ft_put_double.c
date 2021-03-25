/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:44:19 by tvanelst          #+#    #+#             */
/*   Updated: 2021/03/25 15:29:06 by tvanelst         ###   ########.fr       */
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
	if (data[1] == -1)
		size += 7;
	else if (data[1])
		size += data[1] + 1;
	return (size);
}

char		*ft_format_f(double n, int data[3], char *flags)
{
	int		size;
	char	*s;

	size = get_n_size(n, data, flags);
	s = malloc(size + 1);
	if (!s)
		return (0);
	*(s + size--) = 0;
	if (ft_strchr(flags, '#'))
	{
		return (s);
	}
	return (s);
}
