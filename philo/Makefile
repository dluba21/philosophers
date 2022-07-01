SRCS	= 	initializing.c\
		main.c\
		parser_and_creator.c\
		time.c\
		ft_atoi.c\
		
OBJS		= ${SRCS:.c=.o}

NAME		= philo

HEADER		= philo.h

CC		= cc

CFLAGS		= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	@rm -rf ${OBJS}

fclean:	clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re