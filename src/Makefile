# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egermen <egermen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 18:31:51 by egermen           #+#    #+#              #
#    Updated: 2024/05/24 16:50:25 by egermen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=thread -g

RM = rm -rf

SRC = main.c \
		argument_control.c \
		utils.c \
		threads_start.c \
		create.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -c $(SRC)
		$(CC) $(CFLAGS) -o $(NAME) $(SRC)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)
re: fclean all

r: re
f: fclean
c: clean

.phony: all clean fclean re
