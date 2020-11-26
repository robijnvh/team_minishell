/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 13:42:18 by mramadan      #+#    #+#                 */
/*   Updated: 2020/11/26 11:59:16 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(t_data *e, int i)
{
	if (e->params[i + 1][0] == '\"' || e->params[i + 1][0] == '\'')
		e->new_file = ft_substr(e->params[i + 1], 1,
		ft_strlen(e->params[i + 1]) - 2);
	else
		e->new_file = ft_strdup(e->params[i + 1]);
	if (!ft_strcmp(e->params[i], ">"))
	{
		e->re_out != -1 ? close(e->re_out) : 0;
		e->re_out = open(e->new_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (!ft_strcmp(e->params[i], ">>"))
	{
		e->re_out != -1 ? close(e->re_out) : 0;
		e->re_out = open(e->new_file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
}

void	redirect_input(t_data *e, int i)
{
	if (e->params[i + 1][0] == '\"' || e->params[i + 1][0] == '\'')
		e->new_file = ft_substr(e->params[i + 1], 1,
		ft_strlen(e->params[i + 1]) - 2);
	else
		e->new_file = ft_strdup(e->params[i + 1]);
	e->re_in != -1 ? close(e->re_in) : 0;
	e->re_in = open(e->new_file, O_RDONLY);
}

void	do_dup(t_data *e)
{
	if (e->re_out > 0)
	{
		e->fd_write == -1 ? e->fd_write = dup(1) : 0;
		if (e->fd_write < 0 || dup2(e->re_out, 1) < 0)
			free_and_stuff(e, 1, 0);
	}
	if (e->re_in > 0)
	{
		e->fd_read == -1 ? e->fd_read = dup(0) : 0;
		if (e->fd_read < 0 || dup2(e->re_in, 0) < 0)
			free_and_stuff(e, 1, 0);
	}
}

void	redirect(t_data *e)
{
	int i;

	i = 0;
	e->re_out = -1;
	e->re_in = -1;
	while (e->params && e->params[i])
	{
		if ((!ft_strcmp(e->params[i], ">") || !ft_strcmp(e->params[i], ">>"))
		&& e->params[i + 1])
			redirect_output(e, i);
		else if (!ft_strcmp(e->params[i], "<") && e->params[i + 1])
			redirect_input(e, i);
		if (errno)
		{
			error_message(e, 2);
			errno = 0;
			free_array(&e->params);
		}
		free_and_zero(&e->new_file);
		i++;
	}
	do_dup(e);
}
