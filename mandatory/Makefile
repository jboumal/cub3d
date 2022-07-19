# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:10:01 by bel-mous          #+#    #+#              #
#    Updated: 2022/07/13 20:34:15 by bel-mous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
#SRC = 	$(wildcard src/*/*.c)
#\src/cub3d.c

SRC = 	src/parser/parser.c src/cub3d.c src/gnl/get_next_line.c src/gnl/get_next_line_utils.c src/utils/utils.c

INCLUDES = include

OBJ = $(SRC:.c=.o)

CFLAGS =
#CFLAGS = -Wall -Wextra -Werror

LIB = -lmlx -framework OpenGL -framework AppKit

CC = gcc

.c.o: $(SRC)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME) map.cub

.PHONY: $(NAME) all clean fclean re run rerun
