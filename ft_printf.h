/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:01:05 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/25 12:53:23 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H
# include "libft.h"
# include <stdarg.h>
#include <stdio.h>

char	*ft_format_uxp(unsigned long n, char c, int *data, char *flags);
int		ft_printf(const char *fmt, ...);
char	*ft_format_s(char *s, int size);
char	*ft_format_c(char c);
char	*ft_format_di(int n, int *data, char *flags);
#endif