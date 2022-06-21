SRCS 	= 	ft_bzero.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_substr.c\
		ft_strtrim.c\
		ft_strrchr.c\
		ft_strnstr.c\
		ft_strncmp.c\
		ft_strmapi.c\
		ft_strlen.c\
		ft_memcmp.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strjoin.c\
		ft_striteri.c\
		ft_strdup.c\
		ft_strchr.c\
		ft_split.c\
		ft_atoi.c\
		ft_putstr_fd.c\
		ft_putnbr_fd.c\
		ft_putendl_fd.c\
		ft_putchar_fd.c\
		ft_memset.c\
		ft_memmove.c\
		ft_memcpy.c\
		ft_memchr.c\
		ft_itoa.c\
		ft_isprint.c\
		ft_isdigit.c\
		ft_isascii.c\
		ft_isalpha.c\
		ft_isalnum.c\
		ft_calloc.c\

BONUSES	=	ft_lstsize_bonus.c\
		ft_lstnew_bonus.c\
		ft_lstmap_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstadd_back_bonus.c\

OBJS	= ${SRCS:.c=.o}

OBJS_BONUSES = ${BONUSES:.c=.o}

NAME	= libft.a

CC	= gcc

LIBCC	= ar rc

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
all: $(NAME)

$(NAME): $(OBJS)
	${LIBCC} $(NAME) $(OBJS)

bonus: $(NAME) $(OBJS_BONUSES)
	$(LIBCC) $(NAME) $(OBJS) $(OBJS_BONUSES)

clean:
	@rm -rf ${OBJS} ${OBJS_BONUSES}

fclean:	clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus