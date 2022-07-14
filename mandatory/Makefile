# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:10:01 by bel-mous          #+#    #+#              #
#    Updated: 2022/07/14 13:25:14 by vrogiste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

#!!!! DANGER
SRC = 	$(wildcard src/*/*.c)\
		src/cub3d.c

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
	./$(NAME) map.cub

.PHONY: $(NAME) all clean fclean re run rerun
