# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 11:56:55 by mybenzar          #+#    #+#              #
#    Updated: 2019/05/24 19:12:27 by mybenzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= mybenzar.filler
CC		= gcc 
CFLAGS	= -Wall -Wextra -Werror
SOURCES = main.c parse_player.c allocate_free.c debug.c
OBJECTS	= $(SOURCES:.c=.o)
LIBPATH	= ./libft/
LIB		= $(LIBPATH)libft.a
INC		= filler.h

all : $(NAME)

$(NAME): $(LIB) $(OBJECTS) $(INC)
	@echo "\033[92mFillit Objects compiled sucessfully with header.\033[0m"
	@echo
	@echo "\033[92mCompiling filler executable.\033[0m" 
	$(CC) $(CFLAGS) -L$(LIBPATH) -lft -o $(NAME) $(OBJECTS)

$(LIB): $(LIBPATH)*.c
	make -C $(LIBPATH)

clean:
	@echo "\033[92mCleaning filler object files.\033[0m" 
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBPATH) clean

fclean: clean
	@echo "\033[92mRemoving filler executable.\033[0m" 
	rm -f $(NAME)
	@echo "\033[92mRemoving libft.a.\033[0m" 
	cd $(LIBPATH) && rm -f libft.a

re:	fclean all

.PHONY: clean fclean
