# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 11:56:55 by mybenzar          #+#    #+#              #
#    Updated: 2019/05/22 11:57:45 by mybenzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= mybenzar.filler
CC		= gcc 
CFLAGS	= -Wall -Wextra -Werror
SOURCES = 
OBJECTS	= $(SOURCES:.c=.o)
LIBPATH	= ./libft/
LIB		= $(LIBPATH)libft.a
INC		= filler.h

all : $(NAME)

$(NAME): $(LIB) $(OBJECTS) $(INC)
	@echo "\033[92mFillit Objects compiled sucessfully with header.\033[0m"
	@echo
	@echo "\033[92mCompiling fillit executable.\033[0m" 
	$(CC) $(CFLAGS) -L$(LIBPATH) -lft -o $(NAME) $(OBJECTS)

$(LIB): $(LIBPATH)*.c
	make -C $(LIBPATH)

clean:
	@echo "\033[92mCleaning fillit object files.\033[0m" 
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBPATH) clean

fclean: clean
	@echo "\033[92mRemoving fillit executable.\033[0m" 
	rm -f $(NAME)
	@echo "\033[92mRemoving libft.a.\033[0m" 
	cd $(LIBPATH) && rm -f libft.a

re:	fclean all

.PHONY: clean fclean
