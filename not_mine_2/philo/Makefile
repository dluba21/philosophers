SRCS		=	check.c \
				main.c \
				other.c \
				routine.c

OBJ			=	${SRCS:.c=.o}

CC			=	cc

REMOVE		=	rm -f

CFLAGS		=	-Wall -Werror -Wextra -pthread

NAME		=	philo

LIBFT		=	libft/libft.a

HEADER		=	philosopher.h

all:		$(LIBFT) $(HEADER) $(NAME)
$(LIBFT):
			make -C libft/
$(NAME):	$(OBJ) $(HEADER)
			$(CC) ${OBJ} -o ${NAME} ${CFLAGS} ${LIBFT}
clean:		
			@$(REMOVE) $(OBJ)
			make -C libft/ clean
fclean:		clean
			@$(REMOVE) $(NAME)
			make -C libft/ fclean

re:			fclean all

.PHONY:		all clean fclean re