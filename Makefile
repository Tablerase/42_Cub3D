SRC =	raycasting.c \

OBJ =	${SRC:.c=.o}

FLAGS =	-Wall -Wextra -Werror -g3

NAME = raycasting

MLX_NAME = minilibx-linux/Makefile.gen

MLX_LIB = -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz

.c.o:
	cc $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ) $(MLX_NAME)
	cc $(FLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

$(MLX_NAME):
	make -C minilibx-linux

all:	$(NAME) $(MLX_NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
