# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-mous <bel-mous@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:10:01 by bel-mous          #+#    #+#              #
#    Updated: 2022/07/12 18:20:56 by bel-mous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC = 	src/cub3d.c \
		src/event/event.c \
		src/gameloop/gameloop.c \
		src/parser/parser.c \
		src/render/render.c \

INCLUDES = include

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIB = -lmlx -framework OpenGL -framework AppKit

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
	./$(NAME)

.PHONY: $(NAME) all clean fclean re run rerun
