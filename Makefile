SRCS		=	ft_printf.c ft_putnbr_base.c ft_format_str.c

LIBFTSRCS	=

OBJS		=	${SRCS:.c=.o}

CC			=	gcc

CPPFLAGS	=	-Ilibft

FLAGS		=	-Wall -Wextra -Werror

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
