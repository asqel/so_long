SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

NAME = so_long
CC = clang
CFLAGS = -Iminilibx-linux -g -Wall -Werror -Wextra
LDFLAG = -lX11 -lXext


all: $(NAME)

$(NAME): $(OBJ) minilibx-linux/libmlx.a
	$(CC) $(OBJ) minilibx-linux/libmlx.a -o $(NAME) $(CFLAGS) $(LDFLAG)

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


debug: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./so_long map