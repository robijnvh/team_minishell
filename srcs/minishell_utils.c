/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:25:01 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/27 12:06:33 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		index_off(char **array, char *str)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], str))
			return (i);
		i++;
	}
	return (-1);
}

void	prompt(t_data *e)
{
	if (!e->first)
		e->first = write(1, " \e[1;1H\e[2J", 12);
	if (e->is_child == 2)
		ft_putstr_fd("^\\Quit: 3\nminishell> ", 1);
	else if (e->is_child != 1)
		ft_putstr_fd("minishell> ", 1);
	e->is_child = 0;
	g_ctrl_c = 0;
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*newstr;
	int		i;

	if (!s1 || !s2 || !s3)
		return (0);
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
	+ ft_strlen(s3) + 1));
	if (!newstr)
		return (0);
	i = 0;
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_strlcpy(newstr + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3) + 1);
	return (newstr);
}

int		count_new_args(t_data *e)
{
	int i;
	int args;

	i = 0;
	args = 0;
	while (e->params && e->params[i])
	{
		if ((!ft_strcmp(e->params[i], "<") || !ft_strcmp(e->params[i], ">")
		|| !ft_strcmp(e->params[i], ">>")) && e->params[i + 1])
			i += 2;
		else
		{
			args++;
			i++;
		}
	}
	return (args);
}

void	*trim_args(t_data *e)
{
	int		i;
	int		i2;
	char	**new_array;

	if (count_new_args(e) == 0)
		return (free_array(&e->params));
	new_array = malloc(sizeof(char *) * (count_new_args(e) + 1));
	i = 0;
	i2 = 0;
	while (e->params && e->params[i])
	{
		if ((!ft_strcmp(e->params[i], "<") || !ft_strcmp(e->params[i], ">")
		|| !ft_strcmp(e->params[i], ">>")) && e->params[i + 1])
			i += 2;
		else
		{
			new_array[i2] = ft_strdup(e->params[i]);
			i++;
			i2++;
		}
	}
	new_array[i2] = NULL;
	free_array(&e->params);
	return (new_array);
}
