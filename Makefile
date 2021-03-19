SRCS	=	ft_printf.c

BONUS	=

OBJS	=	${SRCS:.c=.o}

OBONUS	=	${BONUS:.c=.o}

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -L libft -lft -I libft

NAME	=	libftprintf.a

RM		= rm -f

.c.o	: ${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

bonus	:	${NAME} ${OBONUS}
			ar rc ${NAME} ${OBONUS}

all		:	${NAME} bonus

clean	:
			${RM} ${OBJS} ${OBONUS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all
