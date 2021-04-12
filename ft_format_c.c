/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:18:19 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/12 21:45:47 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_format_c(va_list ap, t_converter *c)
{
	char	*s;
	char	input;

	if (c->convertion == 'c')
		input = (unsigned char)va_arg(ap, int);
	else
		input = c->convertion;
	s = malloc(2);
	if (!s)
		return (0);
	*s = input;
	*(s + 1) = 0;
	return (s);
}
