# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rvan-hou <rvan-hou@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/17 15:40:10 by Marty         #+#    #+#                  #
#    Updated: 2020/12/02 10:48:38 by Marty         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = ./srcs

SRC =	minishell.c get_line.c cd.c ctrl.c echo.c \
		env_check_input.c env_utils.c env.c \
		export.c exec.c improve_line.c \
		export_utils.c utils.c split_actions.c \
		minishell_utils.c pipe.c redirect.c \
		ft_split_quotes.c trim_for_echo.c write_echo.c \
		utils_2.c ft_split_quotes_utils.c exit.c \
		export_env.c free_and_stuff.c cd_utils.c utils_3.c utils_4.c \
		check_env_vars.c

FILES = $(addprefix $(SRC_DIR)/, $(SRC))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(FILES)
	@echo "Remaking libft.a and libftprintf.a"
	@make re -s -C ./ft_printf
	@cp ./ft_printf/libftprintf.a .
	@cp ./ft_printf/libft/libft.a .
	@gcc $(FLAGS) -I ./include/ $(FILES) libft.a libftprintf.a -o $(NAME)
	@echo "[minishell] Compiled successfuly! [OK]\n"

clean:
	/bin/rm -f *.o
	@make clean -s -C ./ft_printf
	/bin/rm -f libftprintf.a
	/bin/rm -f libft.a

fclean: clean
	@make fclean -s -C ./ft_printf
	/bin/rm -f libftprintf.a
	/bin/rm -f libft.a
	/bin/rm -f minishell

re: fclean all
