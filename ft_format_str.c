/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:24:21 by tvanelst          #+#    #+#             */
/*   Updated: 2021/03/24 10:34:22 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_format_str(char *s, int size)
{
	char	*str;

	if (!s)
		s = "(null)";
	if (size < 0 || (unsigned int)size > ft_strlen(s))
		size = ft_strlen(s);
	str = malloc(size + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s, size + 1);
	return (str);
}
