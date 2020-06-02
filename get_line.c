/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_line.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 11:06:10 by Marty         #+#    #+#                 */
/*   Updated: 2020/06/02 18:16:03 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

char	*ft_strchr2(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (str + 1);
		str++;
	}
	return (0);
}

int		ft_strlen2(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

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

int		check_line(char *str, t_data *e)
{
	int		quote;
	int		sin_quote;
	int		i;

	quote = 0;
	sin_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			quote++;
		else if (str[i] == '\'')
			sin_quote++;
		else if (str[i] == '\n' && quote % 2 == 0 && sin_quote % 2 == 0)
			return (0);
		i++;
	}
	// printf("check4\n");
	return (1);
}

int		get_line(char **line, t_data *e)
{
	static char *str;
	int			ret;

	if (!str)
		str = ft_strdup("");
	if (!str)
		return (-1);
	if (ft_strchr2(str, '\n') && !check_line(str, e))
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
	return (get_line(line, e));
}
