/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:16:19 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/25 10:46:26 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim(char *str, int c)
{
	int i;
	int ret;
	int count;

	i = 0;
	ret = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			ret = i;
			count++;
		}
		i++;
	}
	if (count == 1)
		return (ft_strdup("/"));
	return (ft_substr(str, 0, ret));
}

int		only_cd(t_data *e, int num)
{
	int		i;
	int		slash;

	i = 0;
	slash = 0;
	while (slash != num && e->og_path[i])
	{
		if (e->og_path[i] == '/')
			slash++;
		if (slash == num)
			break ;
		i++;
	}
	e->path ? free(e->path) : 0;
	e->path = ft_substr(e->og_path, 0, i);
	e->path ? 0 : free_and_stuff(e, 0, 1);
	chdir(e->path);
	set_path(e, e->path);
	return (0);
}

int		check_spaces_in_path_2(t_data *e, int i, int check, int sign)
{
	char *tmp;

	if (sign == 0)
	{
		tmp = e->params[i];
		e->params[i] = ft_substr(e->params[i], 0,
		ft_strlen(e->params[i]) - 1);
		e->params[i] ? 0 : free_and_stuff(e, 0, 1);
		free(tmp);
		tmp = e->params[i];
		e->params[i] = ft_strjoin(e->params[i], " ");
		e->params[i] ? 0 : free_and_stuff(e, 0, 1);
		free(tmp);
		check++;
	}
	else
	{
		tmp = e->params[1];
		e->params[1] = ft_strjoin(e->params[1], e->params[i]);
		e->params[1] ? 0 : free_and_stuff(e, 0, 1);
		free(tmp);
	}
	return (check);
}

int		check_spaces_in_path(t_data *e, int i, int check)
{
	int		ret;

	ret = 0;
	while (e->params[i] != NULL)
	{
		if (e->params[i][(ft_strlen(e->params[i]) - 1)] == 92)
		{
			check = check_spaces_in_path_2(e, i, check, 0);
			if (i == 1)
			{
				i++;
				continue ;
			}
			check_spaces_in_path_2(e, i, 0, 1);
			ret = 1;
		}
		else if (i != 1 && check == 1)
		{
			check_spaces_in_path_2(e, i, 0, 1);
			ret = 1;
		}
		check--;
		i++;
	}
	return (ret);
}

int		change_dir(t_data *e, int check)
{
	int		i;

	if (!e->params[1])
		return (only_cd(e, 3));
	i = 1;
	while (e->params[i] != NULL)
	{
		if (!check_cd_arg(e, i))
			return (0);
		if (chdir(e->path) == -1 && chdir(e->params[i]) == -1)
		{
			if (!wrong_cd_arg(e, i, &check))
				break ;
		}
		else
		{
			if (e->params[i] && !ft_strcmp(e->params[i], ".."))
				break ;
			check = 1;
		}
		i++;
	}
	set_path(e, e->path);
	e->path ? free_and_zero(&e->path) : 0;
	return (0);
}
