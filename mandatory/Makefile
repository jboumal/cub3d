# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:10:01 by bel-mous          #+#    #+#              #
#    Updated: 2022/07/25 19:04:07 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

#!!!! DANGER
SRC = 	$(wildcard src/*/*.c)\
		src/cub3d.c

INCLUDES = include

OBJ = $(SRC:.c=.o)


ifeq ($(shell uname), Linux)
#CFLAGS = -Wall -Wextra -Werror -D LINUX
	CFLAGS = -D LINUX
#	LIB = -lmlx -lXext -lX11 -lm
	LIB			= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	CFLAGS = -Wall -Wextra -Werror -D MAC
	LIB = -lmlx -framework OpenGL -framework AppKit
endif

CC = gcc

.c.o: $(SRC)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME) map.cub

.PHONY: $(NAME) all clean fclean re run rerun
