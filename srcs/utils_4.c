/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_4.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 13:34:13 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/27 11:22:04 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_data *e)
{
	e->new_file = NULL;
	e->params = NULL;
	e->pipe_split = NULL;
	e->pipe = NULL;
	e->path = NULL;
	e->bins = NULL;
	e->re_in = -1;
	e->re_out = -1;
	e->pipe_count = 0;
	e->fd_read = -1;
	e->fd_write = -1;
	e->pids = 0;
	e->write = 0;
	errno = 0;
	if (!getcwd(e->buf, PATH_MAX))
		free_and_stuff(e, 1, 0);
}

int		ft_isquote(char c)
{
	return (c == '\"' || c == '\'');
}
