/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_cs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:24:21 by tvanelst          #+#    #+#             */
/*   Updated: 2021/03/25 15:49:13 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_format_s(char *str, int size)
{
	char	*s;
	int		size2;

	if (!str)
		str = "(null)";
	size2 = ft_strlen(str);
	if (size < 0 || (unsigned int)size > size2)
		size = size2;
	s = malloc(size + 1);
	if (!s)
		return (0);
	ft_strlcpy(s, str, size + 1);
	return (s);
}

char	*ft_format_c(char c)
{
	char	*s;

	s = malloc(2);
	if (!s)
		return (0);
	*s = c;
	*(s + 1) = 0;
	return (s);
}
