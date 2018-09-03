# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:04:49 by acauchy           #+#    #+#              #
#    Updated: 2017/12/12 11:41:39 by acauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re compile debug

NAME = fillit

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_NAME =	main.c \
		import.c \
		utils.c \
		output.c \
		resolve.c \
		validate_tetri.c

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH = libft
LIBFT_INCLUDE = -iquote$(LIBFT_PATH)
LIBFT = -L$(LIBFT_PATH) -lft

all: compile

$(OBJ_PATH)/%.o: %.c
	$(CC) -c $(CFLAGS) $< $(LIBFT_INCLUDE) -o $@

$(NAME): $(OBJ)
	$(CC) $^ $(LIBFT) -o $(NAME)

compile:
	mkdir -p $(OBJ_PATH)
	make -C $(LIBFT_PATH)
	make $(NAME)

clean:
	rm -Rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
