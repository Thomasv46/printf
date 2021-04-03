SRCS		=	ft_printf.c ft_format_uxp.c ft_format_cs.c ft_format_di.c ft_format_f.c

LIBFTSRCS	=

OBJS		=	${SRCS:.c=.o}

CC			=	gcc

CPPFLAGS	=	-Ilibft

CFLAGS		=	-Wall -Wextra -Werror

LDFLAGS		=	-L libft

LDLIBS		=	-lft

NAME		=	libftprintf.a

RM			=	rm -f

${NAME}		:	${OBJS}
				$(MAKE) bonus -C libft
				ar rc ${NAME} ${OBJS} ./libft/*.o
				ranlib ${NAME}

all			:	${NAME}

clean		:
				${RM} ${OBJS} ${OBONUS}
				$(MAKE) clean -C libft

fclean		:	clean
				${RM} ${NAME}
				$(MAKE) fclean -C libft

re			:	fclean all
