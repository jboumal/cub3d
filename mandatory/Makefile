# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:10:01 by bel-mous          #+#    #+#              #
#    Updated: 2022/08/04 22:04:56 by vrogiste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
#!!!! DANGER
#SRC = 	$(wildcard src/*/*.c)\
		src/cub3d.c

SRC = 	cub3d.c \
		event/event.c \
		gameloop/update_cam.c gameloop/gameloop.c \
		parse/parse.c parse/parse_map.c parse/parse_textures.c parse/get_map_str.c\
		render/dda.c render/raycasting.c render/textures.c render/mlx_utils.c render/minimap.c render/render.c \
		utils/get_next_line.c utils/min_max.c utils/str_copy.c utils/put.c utils/str.c utils/utils.c utils/vector.c utils/split.c utils/str_alloc.c utils/str_arr.c utils/str_find.c utils/get_first_non_empty_line.c\
		data_struct/dy_str.c

SRC		:= $(addprefix src/,$(SRC))

INCLUDES = include
OBJ = $(SRC:.c=.o)
CC = gcc

ifeq ($(shell uname), Linux)
#CFLAGS = -Wall -Wextra -Werror -D LINUX
	CFLAGS = -I$(INCLUDES) -D LINUX
#	LIB = -lmlx -lXext -lX11 -lm
	LIB			= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
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
