/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:44:19 by tvanelst          #+#    #+#             */
/*   Updated: 2021/03/26 16:32:55 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_n_size(char *s, int data[3], char *flags)
{
	int	size;

	size = ft_strlen(s);
	if (data[1] == -1)
		size += 7;
	else if (data[1])
		size += data[1] + 1;
	return (size);
}

char		*ft_format_f(double n, int data[3], char *flags)
{
	int		size;
	int		size2;
	char	*s;
	char	*s2;

	s2 = ft_format_di(n, data, flags);
	size = get_n_size(s2, data, flags);
	s = malloc(size + 1);
	if (!s)
		return (0);
	*(s + size--) = 0;
	size2 = ft_strlcpy(s, s2, size);
	free(s2);
	*(s + size2++) = '.';
	n = n - (int)n;
	while (size2 < size--)
		n *= 10;
	if ((int)n % 5)
		n = (n + 10) / 10;
	s2 = ft_itoa(n);
	return (s2);
	ft_strlcpy(ft_strchr(s, '.') + 1, s2, 10);
	if (ft_strchr(flags, '#'))
	{
		return (s);
	}
	return (s);
}
