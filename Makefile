SRCS		=	ft_printf.c ft_putnbr_base.c

BONUS		=

OBJS		=	${SRCS:.c=.o}

OBONUS		=	${BONUS:.c=.o}

CC			=	gcc

CPPFLAGS	=	-Ilibft

FLAGS		=	-Wall -Wextra -Werror -L libft -lft

NAME		=	libftprintf.a

RM			= rm -f

${NAME}		:	${OBJS}
				$(MAKE) -C libft
				ar rc ${NAME} ${OBJS}
				ranlib ${NAME}

bonus		:	${NAME} ${OBONUS}
				ar rc ${NAME} ${OBONUS}

all			:	${NAME} bonus

clean		:
				${RM} ${OBJS} ${OBONUS}

fclean		:	clean
				${RM} ${NAME}

re			:	fclean all
