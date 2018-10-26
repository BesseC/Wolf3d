# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbesse <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/01 12:13:48 by cbesse            #+#    #+#              #
#    Updated: 2018/10/26 12:21:12 by cbesse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3d
SRC = init.c main.c dda.c draw.c texture.c parseur.c
SRC_TEST = test.c
OBJ = $(SRC:.c=.o)
OBJ_TEST = $(SRC_TEST:.c=.o)
CC = cc -g3

FLAGS = -Wall -Wextra -Werror `sdl2-config --cflags`
LIB = -Llibft -lft -lSDL2_image `sdl2-config --libs`

all : $(NAME)

$(NAME) : $(OBJ)
	@cd libft && make
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIB)
	@echo "Compilation termine"

%.o : %.c
	@echo "\033[0;36m\033[1ACompilation de $@\033[0m"
	@$(CC) $(FLAGS) -c $<
test :
	@cd libft && make
	@$(CC) $(FLAGS) $(SRC_TEST) -c
	@$(CC) -o test $(FLAGS2) $(OBJ_TEST) $(LIB)
	@echo "Compilation termine"
clean :
	@rm -rf $(OBJ)
	@cd libft && make clean
	@echo "\033[1;32mSuppresion des objets ternime\033[0m"

fclean : clean
	@rm -rf $(NAME) $(LIB)
	@cd libft && make fclean
	@echo "\033[1;32mSuppresion du binaire\033[0m"

re : fclean all
