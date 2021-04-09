/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:31:51 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/09 21:34:31 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_format_n(va_list ap, t_converter *converter)
{
	int	*my_n;

	my_n = va_arg(ap, int *);
	*my_n = converter->counter;
	return (0);
}
