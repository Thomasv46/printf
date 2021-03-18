SRCS	=	ft_printf.c

BONUS	=

OBJS	=	${SRCS:.c=.o}

OBONUS	=	${BONUS:.c=.o}

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -lft

NAME	=	libftprintf.a

RM		= rm -f

.c.o	: ${CC} ${FLAGS} -c -L libft $< -o ${<:.c=.o}

${NAME}	:	libft ${OBJS}
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
