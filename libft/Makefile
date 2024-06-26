# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/28 17:51:05 by rcutte            #+#    #+#              #
#    Updated: 2024/03/08 18:35:19 by rcutte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wextra -Wall -Werror -I $(INCLUDES) -g3
# header path
INCLUDES = ./Includes/
# source path
SRC_PATH = ./Libft/
# files
SRC = ft_isascii.c  ft_memmove.c  ft_strlcpy.c  ft_substr.c\
	ft_atoi.c     ft_isdigit.c  ft_memset.c   ft_strlen.c   ft_tolower.c\
	ft_bzero.c    ft_isprint.c  ft_strchr.c   ft_strncmp.c  ft_toupper.c\
	ft_calloc.c   ft_memchr.c   ft_strdup.c   ft_strnstr.c\
	ft_isalnum.c  ft_memcmp.c   ft_strjoin.c  ft_strrchr.c\
	ft_isalpha.c  ft_memcpy.c   ft_strlcat.c  ft_strtrim.c\
	ft_split.c	ft_itoa.c	ft_strmapi.c	ft_striteri.c\
	ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c\
	ft_lstnew_bonus.c	ft_lstadd_front_bonus.c	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c	ft_lstadd_back_bonus.c	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c	ft_lstiter_bonus.c	ft_lstmap_bonus.c\
	ft_printf/ft_printf.c ft_printf/ft_printf_utils.c\
	ft_printf/ft_printf_unsigned_utils.c\
	gnl/get_next_line.c\
	gnl/get_next_line_utils.c\

# objet libft
OBJ = $(addprefix $(SRC_PATH), $(SRC:.c=.o))

# files projet
PROJET = 

# objet projet
OBJ_PROJET = $(PROJET:.c=.o)

# Tags archivage
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_PROJET)
	$(AR) $(NAME) $?

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@	

clean: 
	rm -f $(OBJ) $(OBJ_PROJET)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# ==================== Custom to improve ==================== #

# Total number of source files
TOTAL_FILES = $(words $(SRC))

# Counter for completed tasks
COMPLETED = 0

# Function to increment the counter and display the progress
define update_progress
    $(eval COMPLETED=$(shell echo $$(($(COMPLETED)+1))))
    $(eval PERCENT=$(shell echo $$((($(COMPLETED) * 100) / $(TOTAL_FILES)))))
    @printf "Progress: [%-50s] %d%%\r" $$(printf '%.0s#' $$(seq -s '' 1 $$(($(PERCENT)/2)))) $(PERCENT)
endef
