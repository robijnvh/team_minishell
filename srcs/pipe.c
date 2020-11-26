/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:00:52 by mramadan      #+#    #+#                 */
/*   Updated: 2020/11/26 11:59:01 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(t_data *e)
{
	int	i;
	int **pipearray;

	i = 0;
	while (e->pipe_split[e->pipe_count + 1])
		e->pipe_count++;
	if (!e->pipe_count)
		return ;
	pipearray = ft_calloc(e->pipe_count, sizeof(int *));
	if (!pipearray)
		free_and_stuff(e, 1, 1);
	while (i < e->pipe_count)
	{
		pipearray[i] = ft_calloc(3, sizeof(int));
		if (!pipearray[i])
			free_and_stuff(e, 1, 1);
		pipe(pipearray[i]) < 0 ? free_and_stuff(e, 1, 1) : 0;
		i++;
	}
	e->pipe = pipearray;
	e->fd_read == -1 ? e->fd_read = dup(0) : 0;
	errno ? free_and_stuff(e, 1, 1) : 0;
	e->fd_write == -1 ? e->fd_write = dup(1) : 0;
	errno ? free_and_stuff(e, 1, 1) : 0;
}

void	set_pipe(t_data *e, int n)
{
	if (!e->pipe_count)
		return ;
	if (n < e->pipe_count)
		dup2(e->pipe[n][1], 1) < 0 ? free_and_stuff(e, 1, 0) : 0;
	if (n > 0)
		dup2(e->pipe[n - 1][0], 0) < 0 ? free_and_stuff(e, 1, 0) : 0;
}

void	close_pipes(t_data *e, int n)
{
	int i;

	i = 0;
	if (!e->pipe_count)
		return ;
	dup2(e->fd_read, 0) < 0 ? free_and_stuff(e, 1, 0) : 0;
	dup2(e->fd_write, 1) < 0 ? free_and_stuff(e, 1, 0) : 0;
	if (n < e->pipe_count)
		close(e->pipe[n][1]) < 0 ? free_and_stuff(e, 1, 0) : 0;
	if (n > 0)
		close(e->pipe[n - 1][0]) < 0 ? free_and_stuff(e, 1, 0) : 0;
	if (n == e->pipe_count)
	{
		while (i < e->pipe_count)
		{
			free(e->pipe[i]);
			i++;
		}
		e->pipe ? free(e->pipe) : 0;
		e->pipe = NULL;
	}
}
