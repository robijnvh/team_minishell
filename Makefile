# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rvan-hou <rvan-hou@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/17 15:40:10 by Marty         #+#    #+#                  #
#    Updated: 2020/06/03 16:34:00 by rvan-hou      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC =	minishell.c get_line.c cd.c ctrl.c dir.c echo.c env_check_input.c \
		env_utils.c env.c exec.c pwd.c write_to_file.c \
		utils.c split.c minishell_utils.c export.c get_line_utils.c \
		split_actions.c

OBJ = $(SRC:.c=.o)

FLAGS = 

LIBFT = ./srcs/libft.a

NAME = minishell


all: $(NAME)
%.o: %.c
	@printf "[minishell] Compiling [.:]\r"
	@gcc $(FLAGS) -c $< -o $@
	@printf "[minishell] Compiling [:.]\r"
$(NAME): $(OBJ)
	@printf "[minishell] Compiled successfuly! [OK]\n"
	@gcc $(FLAGS) $(OBJ) $(LIBFT) -g -o $(NAME)


# $(NAME): $(OBJ)
# 	gcc $(FLAGS) $(LIBFT) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all
