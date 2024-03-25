# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 18:08:42 by rcutte            #+#    #+#              #
#    Updated: 2024/03/25 13:52:02 by rcutte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################### Program ######################

NAME = cub3D

all: $(NAME)

####################### FLAGS #######################

CC = cc
CFLAGS = -Wextra -Wall -Werror -g3
MATH = -lm

ADD_FLAGS = $(MATH) $(MLX_FLAGS)

####################### LIBS ########################

###################### Libft ########################

LIB_PATH = ./libft
LIBFT_Includes = ./libft/Includes
LIBFT = $(LIB_PATH)/libft.a

$(LIBFT):
	make -sC $(LIB_PATH)
	@if [ -f $(LIB_PATH)/libft.a ]; then \
		echo "$(ARCHIVED)\
╭──────────────────────────────────────────────────╮\n\
│                   Libft Created                  │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi
	
lib_clean:
	@if [ -f $(LIB_PATH)/Libft/ft_tolower.o ]; then \
		make -sC $(LIB_PATH) clean; \
		echo "$(ORANGE)Libft Objects Cleaned$(RESET)"; \
	fi

lib_fclean:
	@if [ -f $(LIB_PATH)/libft.a ]; then \
		make -sC $(LIB_PATH) fclean; \
		echo "$(ORANGE)Libft Library Delete$(RESET)"; \
	fi

###################### MiniLibX ######################

OS = $(shell uname)

MLX_PATH = ./mlx

MLX = $(MLX_PATH)/libmlx.a

ifeq ($(OS), Linux)
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11
else
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
endif

$(MLX):
	@if [ ! -d $(MLX_PATH) ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git mlx \
			2> /dev/null ; \
	fi
	@if [ ! -f $(MLX) ]; then \
		make -sC $(MLX_PATH) > /dev/null 2>&1 ; \
		echo "$(ARCHIVED)\
╭──────────────────────────────────────────────────╮\n\
│              📐 MiniLibX Created 📐              │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi
	@if [ ! -f $(MLX) ]; then \
		rm -rf $(MLX_PATH); \
		echo "$(RED)MiniLibX Installation Failed$(RESET)"; \
	fi

mlx_clean:
	@if [ -f $(MLX_PATH)/Makefile.gen ]; then \
		make -sC $(MLX_PATH) clean > /dev/null 2>&1 ; \
		echo "$(ORANGE)MiniLibX Library Cleaned$(RESET)"; \
	fi

mlx_delete:
	@if [ -d $(MLX_PATH) ]; then \
		rm -rf $(MLX_PATH); \
		echo "$(RED)MiniLibX Deleted$(RESET)"; \
	fi

###################### Mandatory #####################

# header path
INCLUDES = ./include
# source path
SRC_PATH = ./src/mandatory

# files

SRC = main.c \
		$(PARSING) \
		$(UTILS) \
		$(DATA) \
		$(EVENTS) \
		$(RAYCASTING) \
		$(GRAPHICS) \

UTILS = utils/mem_free.c \

DATA = data/player_init.c \

RAYCASTING = raycasting/raycasting.c \
		raycasting/raycasting_params.c \
		raycasting/raycasting_lines.c \
		raycasting/raycasting_textures.c \
		raycasting/raycasting_movements.c \
		raycasting/raycasting_rotations.c \

GRAPHICS = graphics/graphics_server.c \
		graphics/colors.c \
		graphics/graphics_pixel.c \
		graphics/graphics_shapes.c \
		graphics/graphics_shapes_lines.c \

EVENTS = events/event_handlers.c \

PARSING = parsing/parsing_colors.c \
		parsing/parsing_map.c \
		parsing/parsing_free.c \
		parsing/parsing_textures.c \
		parsing/parsing_utils.c \
		parsing/parsing.c \
		parsing/parsing_map_collect.c \
		parsing/parsing_map_size.c \
		parsing/parsing_map_utils.c \
		parsing/parsing_init_player_direction.c \
		parsing/parsing_init.c \
		parsing/parsing_map_valid_tiles.c \
		parsing/parsing_colors_utils.c \
		minimap_bonus.c \

# objet libft
OBJ = $(addprefix $(SRC_PATH)/,$(SRC:.c=.o))

###################### Bonus ########################

NAME_BONUS = program_bonus
SRC_BONUS_PATH = ./src/bonus
SRC_BONUS = \

OBJ_BONUS = $(addprefix $(SRC_BONUS_PATH)/,$(SRC_BONUS:.c=.o))

bonus: $(NAME_BONUS)

rebonus: re_msg fclean bonus

##################### Building ######################

$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(ADD_FLAGS) -o $(NAME_BONUS)
	@if [ -f $(NAME_BONUS) ]; then \
		echo "$(COMPILED)\
╭──────────────────────────────────────────────────╮\n\
│             🌟 Program Bonus Compiled 🌟         │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi
	@if [ ! -f $(NAME_BONUS) ]; then \
		@echo "$(FAILED)\
╭──────────────────────────────────────────────────╮\n\
│         Program Bonus Compilation Failed         │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi

$(NAME): $(LIBFT) $(MLX) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(ADD_FLAGS) -o $(NAME)
	@if [ -f $(NAME) ]; then \
		echo "$(COMPILED)\
╭──────────────────────────────────────────────────╮\n\
│                 Program Compiled                 │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi
	@if [ ! -f $(NAME) ]; then \
		echo "$(RED)$(RESET)"; \
		@echo "$(FAILED)\
╭──────────────────────────────────────────────────╮\n\
│            Program Compilation Failed            │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi

%.o : %.c
	$(CC) -c $(CFLAGS) -I$(INCLUDES) -I$(LIBFT_Includes) -I$(MLX_PATH) -o $@ $<

##################### Commands ######################

clean: clean_msg lib_clean 
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean lib_fclean mlx_clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	
re: re_msg fclean all

####################### Tests ########################

ARGS = ./assets/maps/small.cub

exec: all exec_msg
	@./$(NAME) $(ARGS)

ARGS_BONUS = 

exec_bonus: clean bonus exec_msg
	@./$(NAME_BONUS) $(ARGS_BONUS)

###################### Valgrind/Debug ######################

valgrind: clean all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
	./$(NAME) $(ARGS)

valgrind_fd: clean all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
	--trace-children=yes --track-fds=yes \
	./$(NAME) $(ARGS)

lldb: clean all
	@lldb ./$(NAME) $(ARGS)

# lldb_bonus: clean bonus
# 	@lldb ./$(NAME_BONUS) $(ARGS_BONUS)

################### Special Target ###################

.PHONY: all clean fclean re \
	bonus rebonus exec exec_bonus valgrind \
	lib_clean lib_fclean lldb lldb_bonus

.SILENT: $(NAME) $(OBJ) $(OBJ_BONUS) $(LIBFT) bonus

###################### Messages ######################
compile_msg:
	@echo "$(COMPILED)\
	╭──────────────────────────────────────────────────╮\n\
	│                 Program Compiled                 │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

clean_msg:
	@echo "$(GREY)\
	╭──────────────────────────────────────────────────╮\n\
	│              🧹 Cleaning Objects 🧹              │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

re_msg:
	@echo "$(PROGRAM)\
	╭──────────────────────────────────────────────────╮\n\
	│    🚧 Recreation of Program and Libraries 🚧     │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

exec_msg:
	@echo "$(EXEC)\
	╭──────────────────────────────────────────────────╮\n\
	│                 Executing Program                │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

###################### Colors #######################

# ANSI escape codes for colors and formatting
# Format: \033[<attribute>;<foreground>;<background>m

EXEC = \033[1;94m
PROGRAM = \033[1;95m
COMPILED = \033[1;92m
ARCHIVED = \033[1;93m
FAILED = \033[0;31m

# Attributes (0 to 7)
RESET = \033[0m
BOLD = \033[1m
DIM = \033[2m
UNDERLINE = \033[4m
REVERSED = \033[7m

# Foreground Colors (30 to 37)
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

GREY = \033[38;5;240m

# Highlight (Bright) Foreground Colors (90 to 97)
BRIGHT_BLACK = \033[0;90m
BRIGHT_RED = \033[0;91m
BRIGHT_GREEN = \033[0;92m
BRIGHT_YELLOW = \033[0;93m
BRIGHT_BLUE = \033[0;94m
BRIGHT_PURPLE = \033[0;95m
BRIGHT_CYAN = \033[0;96m
BRIGHT_WHITE = \033[0;97m

# Background Colors (40 to 47)
BG_BLACK = \033[0;40m
BG_RED = \033[0;41m
BG_GREEN = \033[0;42m
BG_YELLOW = \033[0;43m
BG_BLUE = \033[0;44m
BG_PURPLE = \033[0;45m
BG_CYAN = \033[0;46m
BG_WHITE = \033[0;47m

# Highlight (Bright) Background Colors (100 to 107)
BG_BRIGHT_BLACK = \033[0;100m
BG_BRIGHT_RED = \033[0;101m
BG_BRIGHT_GREEN = \033[0;102m
BG_BRIGHT_YELLOW = \033[0;103m
BG_BRIGHT_BLUE = \033[0;104m
BG_BRIGHT_PURPLE = \033[0;105m
BG_BRIGHT_CYAN = \033[0;106m
BG_BRIGHT_WHITE = \033[0;107m
