NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ./libft/libft.a
PRINTF = ./libft/ft_printf/libftprintf.a

SRCS =  fract-ol_42/src/main.c fract-ol_42/pars/parsing.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB):
	$(MAKE) -C libft/
$(PRINTF):
	$(MAKE) -C libft/ft_printf/ft_printf.h

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) -L./minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz $(LIB) $(PRINTF) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iminilibx-linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C libft/ libft/ft_printf/

fclean: clean
	$(MAKE) fclean -C libft/ libft/ft_printf/
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)