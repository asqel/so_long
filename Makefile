SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

NAME = so_long
CC = cc
CFLAGS = -Iminilibx-linux -lX11 -lXext -g


all: $(NAME)

$(NAME): $(OBJ) minilibx-linux/libmlx.a
	$(CC) $(OBJ) minilibx-linux/libmlx.a -o $(NAME) $(CFLAGS)

minilibx-linux/libmlx.a:
	make -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean