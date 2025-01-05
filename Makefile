# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 04:15:44 by meghribe          #+#    #+#              #
#    Updated: 2025/01/04 02:40:31 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol

CC := cc
CFLAGS := -Wall -Wextra -Werror -O3 -fsanitize=address -g
INCLUDES := -I . -I ./MLX42/include

SRCS := main.c calcs.c mandelbrot.c julia.c utils.c 
OBJS := $(SRCS:.c=.o)

MLX := ./MLX42
LIBMLX := $(MLX)/build/libmlx42.a
LIBS := $(LIBMLX) -ldl -lglfw -lm

all: $(NAME)

$(NAME): $(OBJS)
	cmake -B $(MLX)/build $(MLX)
	cmake --build $(MLX)/build -j4
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)


%.o: %.c Makefile fractol.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@if [ -d $(MLX)/build ]; then cmake --build $(MLX)/build --target clean; fi

fclean: clean
	rm -f $(NAME)
	@if [ -d $(MLX)/build ]; then rm -rf $(MLX)/build; fi

re: fclean all

.PHONY: all clean fclean re

