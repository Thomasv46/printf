/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:01:05 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/04 14:44:01 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct s_converter
{
	int		width;
	int		precision;
	char	flags[6];
	char	convertion;
}				t_converter;

typedef struct s_tuple
{
	char	*str;
	char	*(*func)(va_list, t_converter);
}				t_tuple;

int		ft_printf(const char *fmt, ...);
char	*ft_format_uxp(va_list ap, t_converter converter);
char	*ft_format_s(va_list ap, t_converter converter);
char	*ft_format_c(va_list ap, t_converter converter);
char	*ft_format_di(va_list ap, t_converter converter);
char	*ft_format_f(va_list ap, t_converter converter);
#endif
