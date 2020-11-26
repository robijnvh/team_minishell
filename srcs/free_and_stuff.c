/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_stuff.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 10:50:58 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/26 13:49:00 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(t_data *e, int error)
{
	if (error == 1)
		ft_printf(2, "minishell: %s\n", strerror(errno));
	else if (error == 2)
		ft_printf(2, "minishell: %s: %s\n", e->new_file, strerror(errno));
	else if (error == 3)
	{
		ft_printf(2, "minishell: .: filename argument required\n");
		ft_printf(2, ".: usage: . filename [arguments]\n");
	}
	else if (error == 4)
		ft_printf(2, "minishell: %s: %s\n", e->params[0], strerror(errno));
	else if (error == 5)
		ft_printf(2, "minishell: %s: command not found\n", e->params[0]);
	else if (error == 6)
		ft_printf(2, "minishell: %s: No such file or directory\n",
		e->params[0]);
	else if (error == 7)
		ft_printf(2, "minishell: %s: is a directory\n", e->params[0]);
	else if (error == 8)
		write(1, "exit\n", 5);
	else if (error == 9)
		ft_printf(2, "exit\nminishell: exit: too many arguments\n");
	else if (error == 10)
		ft_printf(2, "exit\nminishell: exit: %s: numeric argument required\n",
		e->params[1]);
}

void	free_and_zero(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_and_stuff(t_data *e, int error, int ex)
{
	return_values(e);
	e->fd_write != -1 ? dup2(e->fd_write, 1) : 0;
	e->fd_read != -1 ? dup2(e->fd_read, 0) : 0;
	if (error)
	{
		error_message(e, error);
		!e->ret ? e->ret = 1 : 0;
	}
	e->new_file ? free(e->new_file) : 0;
	e->path ? free(e->path) : 0;
	e->params ? free_array(&e->params) : 0;
	e->pipe_split ? free_array(&e->pipe_split) : 0;
	e->bins ? free_array(&e->bins) : 0;
	init_struct(e);
	if (ex)
	{
		e->cmds ? free_array(&e->cmds) : 0;
		if (ex == 2)
			exit(0);
		else
		{
			write(1, "exit\n", 5);
			exit(1);
		}
	}
}

void	*free_array(char ***array)
{
	int i;

	i = 0;
	if (!*array)
		return (NULL);
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
	return (NULL);
}
