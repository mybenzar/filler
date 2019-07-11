# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 11:56:55 by mybenzar          #+#    #+#              #
#    Updated: 2019/07/11 18:40:40 by mybenzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= mybenzar.filler
CC		= clang 
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra 
SOURCES = main.c parse_player.c ft_free.c parse_piece.c strategy.c \
		  check_place.c distance.c parse_helper.c strategy_helper.c \
		  debug.c

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
LIBPATH	= ./libft/
LIBSRC = srcs/
LIB		= $(LIBPATH)libft.a
INC		= filler.h
HEADER = .

all : $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	@echo "\033[92mFillit Objects compiled sucessfully with header.\033[0m"
	@echo
	@echo "\033[92mCompiling filler executable.\033[0m" 
	$(CC) $(CFLAGS) $(OBJECTS) -I$(HEADER) -L$(LIBPATH) -lft -o $(NAME)

$(OBJECTS): %.o: %.c $(INC) Makefile
	$(CC) $(CFLAGS) -I$(HEADER) -c $<

$(LIB): $(LIBPATH)$(LIBSRC)*.c
	$(MAKE) -C $(LIBPATH)

clean:
	@echo "\033[92mCleaning filler object files.\033[0m" 
	$(RM) $(OBJECTS)
	$(MAKE) clean -C $(LIBPATH)

fclean: clean
	@echo "\033[92mRemoving filler executable.\033[0m" 
	$(RM) $(NAME)
	@echo "\033[92mRemoving libft.a.\033[0m" 
	$(MAKE) fclean -C $(LIBPATH)

re:	fclean all

#.PHONY: clean fclean re all
