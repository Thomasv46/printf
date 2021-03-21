/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:01:05 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/03/21 22:19:54 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H
# include "libft.h"
# include <stdarg.h>
#include <stdio.h>

char		*ft_putnbr_base(unsigned long n, char c, char *flags);
#endif