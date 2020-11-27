# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rvan-hou <rvan-hou@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/28 18:16:52 by rvan-hou      #+#    #+#                  #
#    Updated: 2020/11/27 11:23:28 by Marty         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = printf.h

FLAGS = -Wall -Wextra -Werror

SRC =	ft_printf.c \
		getnumbers.c \
		libft_utils.c  \
		printchar.c \
		printstring.c \
		printdigit.c \
		ll_printdigit.c \
		printdigit_utils.c \
		ll_printdigit_utils.c \
		printunsigned_int.c \
		printunsigned_int_utils.c \
		ll_printunsigned_int.c \
		ft_printpercent.c \
		printhex.c \
		printhex_utils.c \
		ll_printhex.c \
		printptr.c \
		setptr.c \

REG_OBJ = $(SRC:.c=.o)

OBJ = $(REG_OBJ)

all: $(NAME)

$(NAME): $(OBJ)
	@make re -s -C ./libft
	@cp ./libft/libft.a .
	gcc -c $(SRC)
	ar -rc $(NAME) $?

clean:
	@make clean -s -C ./libft
	/bin/rm -f libft.a
	/bin/rm -f ./libft/libft.a
	/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -s -C ./libft
	/bin/rm -f libft.a
	/bin/rm -f $(NAME)

re: fclean all
