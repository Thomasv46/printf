/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:31:51 by tvanelst          #+#    #+#             */
/*   Updated: 2021/04/10 13:27:41 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_format_n(va_list ap, t_converter *converter)
{
	int		*my_n;
	char	**tab;
	int		i;

	my_n = va_arg(ap, int *);
	i = 0;
	tab = (char*[]){"hh", "h", "l", "ll"};
	while (i < 4 && ft_strncmp(converter->lenght_modifier, tab[i], 3))
		i++;
	if (i == 0)
		*(signed char *)my_n = converter->counter;
	else if (i == 1)
		*(short int *)my_n = converter->counter;
	else if (i == 2)
		*(long int *)my_n = converter->counter;
	else if (i == 3)
		*(long long int *)my_n = converter->counter;
	else
		*(int*)my_n = converter->counter;
	return (0);
}
