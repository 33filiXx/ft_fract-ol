NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = fract-ol_42/pars/parsing.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)