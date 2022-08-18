
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:10:01 by bel-mous          #+#    #+#              #
#    Upd#    Updated: 2022/08/17 18:05:46 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
#!!!! DANGER
#SRC = 	$(wildcard src/*/*.c)\
		src/cub3d.c

SRC = 	main.c \
		event/event.c \
		gameloop/update_cam.c gameloop/gameloop.c \
		parsing/check_map.c parsing/parse.c parsing/parse_map.c parsing/parse_textures.c parsing/get_map_str.c\
		render/routines.c render/skycasting.c render/floorcasting.c render/dda.c render/raycasting.c render/mlx_utils.c render/minimap.c render/render.c \
		utils/utils.c utils/get_next_line.c utils/min_max.c utils/copy.c utils/put.c utils/str.c utils/vector.c utils/split.c utils/str_alloc.c utils/str_arr.c utils/find.c utils/get_next_non_empty_line.c utils/x_alloc.c\
		utils/swap.c utils/mouse_move.c utils/error.c utils/color.c \
		data_struct/dy_str.c

ifneq ($(shell uname), Linux)
	SRC +=	utils/mlx_mouse.m
endif

SRC		:= $(addprefix src/,$(SRC))

INCLUDES = include
OBJ1 = $(SRC:.c=.o)
OBJ = $(OBJ1:.m=.o)
CC = gcc

ifeq ($(shell uname), Linux)
#CFLAGS = -Wall -Wextra -Werror -D LINUX
	CFLAGS = -I$(INCLUDES) -D LINUX
#LIB = -lpthread -#mlx -lXext -lX11 -lm
	LIB			= -lpthread	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	CFLAGS = -Wall -Wextra -I$(INCLUDES) -D MAC
	LIB = -lmlx -framework OpenGL -framework AppKit
endif


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME) map/minimalist.cub

.PHONY: all clean fclean re
