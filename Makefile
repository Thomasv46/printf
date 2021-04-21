# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/21 13:23:10 by tvanelst          #+#    #+#              #
#    Updated: 2021/04/21 13:28:02 by tvanelst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_printf.c ft_format_uxp.c ft_format_s.c ft_format_di.c	\
				ft_format_f_bonus.c ft_format_c.c ft_format_n_bonus.c		\
				ft_format_e_bonus.c ft_format_g_bonus.c ft_converter.c

BONUS		=	ft_format_f_bonus.c ft_format_e_bonus.c ft_format_g_bonus.c \
				ft_format_n_bonus.c

OBJS		=	${SRCS:.c=.o}

OBONUS		=	${BONUS:.c=.o}

CC			=	gcc

CPPFLAGS	=	-Ilibft

CFLAGS		=	-Wall -Wextra -Werror

LDFLAGS		=	-L libft

LDLIBS		=	-lft

NAME		=	libftprintf.a

RM			=	rm -f

${NAME}		:	${OBJS}
				$(MAKE) all -C libft
				ar rcs ${NAME} ${OBJS} ./libft/*.o

bonus		:	${NAME} ${OBONUS}
				ar rcs ${NAME} ${OBONUS}

all			:	bonus

clean		:
				${RM} ${OBJS} ${OBONUS}
				$(MAKE) clean -C libft

fclean		:	clean
				${RM} ${NAME}
				$(MAKE) fclean -C libft

re			:	fclean all

.PHONY		: 	all clean fclean re
