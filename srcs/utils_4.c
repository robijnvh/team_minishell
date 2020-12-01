/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_4.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 13:34:13 by Marty         #+#    #+#                 */
/*   Updated: 2020/12/01 11:41:51 by robijnvanho   ########   odam.nl         */
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

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

void	write_backslash(t_data *e, char *str, int *i, int param)
{
	int	count;

	count = 0;
	if (ft_strlen(str) == 1 && str[0] == '\\' && param)
	{
		e->write = write(1, "\\", 1);
		return ;
	}
	while (str[*i] == '\\')
	{
		(*i)++;
		count++;
	}
	if (count % 2 != 0 && (ft_isspace(str[*i]) || str[*i] == '\0') && !param)
	{
		e->write = write(1, "\b\bError: multiline command", 26);
		return ;
	}
	count = count / 2;
	while (count > 0)
	{
		e->write = write(1, "\\", 1);
		count--;
	}
}
