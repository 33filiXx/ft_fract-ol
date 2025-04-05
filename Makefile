NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ./libft/libft.a


SRCS =  fract-ol_42/src/main.c fract-ol_42/pars/parsing.c fract-ol_42/src/hooks.c fract-ol_42/src/render.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB):
	$(MAKE) -C libft/


$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) -L./minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz $(LIB)  -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iminilibx-linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C libft/ 

fclean: clean
	$(MAKE) fclean -C libft/ 

re: fclean all 

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)