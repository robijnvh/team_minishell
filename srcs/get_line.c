/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_line.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 11:06:10 by Marty         #+#    #+#                 */
/*   Updated: 2020/09/01 14:12:37 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int		write_line(char *str, char **line, int ret)
{
	int i;

	i = 0;
	*line = malloc(sizeof(char) * ft_strlen2(str) + 1);
	if (!*line)
	{
		free(str);
		return (-1);
	}
	while (str[i] && str[i] != '\n')
	{
		(*line)[i] = str[i];
		i++;
	}
	(*line)[i] = '\0';
	if (ret == 0)
		free(str);
	return (0);
}

char	*get_that_line(char *str, char **line)
{
	int		check;
	char	*tmp;

	check = write_line(str, line, 1);
	if (check == -1)
		return (0);
	tmp = str;
	str = ft_strdup(ft_strchr2(str, '\n'));
	free(tmp);
	if (!str)
		return (0);
	return (str);
}

char	*read_more(char *str, int *ret)
{
	char buf[BUF_SIZE + 1];
	char *tmp;

	*ret = read(0, buf, BUF_SIZE);
	if (*ret < 0)
	{
		free(str);
		return (0);
	}
	buf[*ret] = '\0';
	tmp = str;
	str = ft_strjoin(str, buf);
	free(tmp);
	if (!str)
		return (0);
	return (str);
}

int		get_line(char **line)
{
	static char *str;
	int			ret;

	if (!str)
		str = ft_strdup("");
	if (!str)
		return (-1);
	if (ft_strchr2(str, '\n'))
	{
		str = get_that_line(str, line);
		if (!str)
			return (-1);
		return (1);
	}
	else
		str = read_more(str, &ret);
	if (!str)
		return (-1);
	if (ret == 0)
		return (write_line(str, line, 0));
	return (get_line(line));
}
