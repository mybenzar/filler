# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 11:25:47 by mybenzar          #+#    #+#              #
#    Updated: 2019/05/24 15:23:10 by mybenzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a
HEADERS = libft.h

SRCS =	ft_bzero.c ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_toupper.c\
		ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_strdup.c\
		ft_strlen.c ft_strnew.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c\
		ft_strlcat.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl_fd.c\
		ft_putendl_fd.c ft_putendl.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c\
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strdel.c ft_putstr_fd.c\
		ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_isdigit.c\
		ft_strmap.c ft_strmapi.c  ft_strncmp.c ft_atoi.c ft_isalpha.c\
		ft_strnequ.c ft_strnew.c ft_strrchr.c ft_strsplit.c ft_isascii.c\
		ft_strstr.c ft_strnstr.c ft_strsub.c ft_strtrim.c ft_tolower.c\
		ft_isalnum.c ft_isprint.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c\
		ft_lstadd.c ft_lstmap.c ft_lstiter.c ft_power.c ft_atoi_base.c\
		ft_strnlen.c ft_lstsort.c ft_lstswap_content.c ft_lst_pushback.c\
		ft_lstsize.c ft_itoabase.c ft_convert_itoc.c ft_numlen_base.c\
		ft_convert_dec.c ft_intsize.c ft_strjoin_free.c ft_swap.c ft_strrev.c\
		ft_putnstr.c ft_strupper.c print_nchar.c ft_dftoa.c ft_max.c ft_min.c\
		ft_str_isdigit.c vlq_cmp.c\
		get_next_line.c \
		print_utils.c args_conv.c ft_printf.c print_float.c get_flags.c\
		parsing_utils.c get_size.c free_functions.c fill_padding.c\
		print_nb.c print_char.c print_str.c print_nb_padding.c get_res.c\
		get_res_l.c ft_frexp.c ft_ldftoa.c ft_frexpl.c ft_bintowhole.c\
		ft_bintodec.c vlq_pow.c get_exp.c get_exp_l.c float_converter.c\
		ft_round.c vlq_sum.c vlq_initialize.c vlq_conv.c vlq_shift.c\
		vlq_mult.c vlq_calc_info.c ft_round_utils.c\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) :
	$(CC) -c $(FLAGS) $(SRCS) -I $(HEADERS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean
