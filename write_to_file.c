/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_to_file.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:21:04 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/02 10:23:26 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_wtf(t_data *e)
{
	e->wtf_i[e->i] = index_off(e->params[e->i], ">");
	e->trunc[e->i] = e->wtf_i[e->i] >= 0 ? 1 : 0;
	e->append[e->i] = e->wtf_i[e->i] >= 0 ? 0 : 1;
	if (e->append[e->i] == 1)
		e->wtf_i[e->i] = index_off(e->params[e->i], ">>");
	e->new_file[e->i] = ft_strdup(e->params[e->i][e->wtf_i[e->i] + 1]);
	if (!ft_strcmp(e->cmd[e->i], ">") || !ft_strcmp(e->cmd[e->i], ">>"))
		open_file(e);
	else
	{
		e->params[e->i][e->wtf_i[e->i]] = NULL;
		free(e->params[e->i][e->wtf_i[e->i]]);
		e->params[e->i][e->wtf_i[e->i] + 1] = NULL;
		free(e->params[e->i][e->wtf_i[e->i] + 1]);
	}
	return (0);
}

int		wtf(t_data *e, char *s, int i)
{
	int		fd;
	int		j;
	char	div;

	fd = open(e->new_file[e->i], O_RDWR | O_APPEND, 0777);
	if (fd < 0 || e->trunc[e->i])
	{
		fd = open(e->new_file[e->i], O_RDWR | O_CREAT | O_TRUNC, 0777);
		e->trunc[e->i] = 0;
	}
	write(fd, s, ft_strlen(s));
	// div = ft_strnstr(e->params[e->i][i + 1], ">", ft_strlen(e->params[e->i][i + 1])) ? '\n' : ' ';
	div = '\n';
	// div = e->trunc[e->i] ? '\n' : ' ';
	write(fd, &div, 1);
	close(fd);
	return (0);
}

int		open_file(t_data *e)
{
	int fd;
	// char *input;
	// int ret;

	fd = open(e->params[e->i][0], O_RDWR | O_APPEND, 0777);
	if (fd < 0 || !ft_strcmp(e->cmd[e->i], ">"))
		fd = open(e->params[e->i][0], O_RDWR | O_CREAT | O_TRUNC, 0777);
	// while (1)
	// {
	// 	ret = get_line(&input);
	// 	if (ret < 0)
	// 	{
	// 		free(input);
	// 		return (0);
	// 	}
	// 	write(fd, input, ft_strlen(input));
	// 	write(fd, "\n", 1);
	// 	free(input);
	// }
	close(fd);
	return (1);
}
