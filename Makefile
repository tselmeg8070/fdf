# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 15:27:09 by tadiyamu          #+#    #+#              #
#    Updated: 2023/02/11 15:30:56 by tadiyamu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
LIBFT = libft.a
MINILIBX = libmlx_Linux.a
FLAGS = -Wall -Wextra -Werror
FILES = main \
		fdf_prepare_map \
		fdf_prepare_utils \
		fdf_prepare_split \
		fdf_points_cal \
		fdf_connect_points \
		fdf_hooks \
		get_next_line \
		get_next_line_utils

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(FLAGS) $(SRCS) -Lminilibx-linux \
	-lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz \
	-L./libft -lft  -o $(NAME)

all: $(NAME)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	make -C libft

$(MINILIBX):
	make -C minilibx-linux

clean:
	make clean -C libft
	make clean -C minilibx-linux
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
