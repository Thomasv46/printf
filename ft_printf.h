/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:01:05 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/22 21:15:22 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H
# include "libft.h"
# include <stdarg.h>
#include <stdio.h>

char	*ft_putnbr_base(unsigned long n, char c, int data[2], char *flags);
int		ft_printf(const char *fmt, ...);
char	*ft_format_str(char *s, int size);
char	*ft_putnbr_signed(int n, int data[3], char *flags);
#endif