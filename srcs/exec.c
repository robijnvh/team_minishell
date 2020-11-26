/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:13:11 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/26 11:59:22 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_cmd_in_bin(t_data *e, char **bins, char *cmd)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;

	i = 0;
	while (bins[i])
	{
		dir = opendir(bins[i]);
		errno ? free_and_stuff(e, 1, 1) : 0;
		while (1)
		{
			sd = readdir(dir);
			errno ? free_and_stuff(e, 1, 1) : 0;
			if (sd && !ft_strcmp(sd->d_name, cmd))
			{
				closedir(dir) < 0 ? free_and_stuff(e, 1, 1) : 0;
				return (i);
			}
			if (!sd)
				break ;
		}
		closedir(dir) < 0 ? free_and_stuff(e, 1, 1) : 0;
		i++;
	}
	return (-1);
}

char	*construct_cmd_path(t_data *e)
{
	char	*abspath;
	char	*tmp;
	int		i;

	if (e->params[0][0] == '/')
		return (NULL);
	if (ft_strnstr(e->params[0], "../", 3))
	{
		i = 0;
		abspath = ft_strdup(e->buf);
		while (ft_strnstr(e->params[0] + i, "../", 3))
		{
			tmp = abspath;
			abspath = trim(tmp, '/');
			free(tmp);
			i += 3;
		}
		return (ft_strjoin3(abspath, "/", e->params[0] + i));
	}
	i = find_cmd_in_bin(e, e->bins, e->params[0]);
	if (i < 0)
		return (NULL);
	abspath = ft_strjoin3(e->bins[i], "/", e->params[0]);
	return (abspath);
}

void	del_quotes(t_data *e)
{
	int		i;
	char	*tmp;

	i = 0;
	while (e->params && e->params[i])
	{
		if (e->params[i][0] == '\"' || e->params[i][0] == '\'')
		{
			tmp = ft_substr(e->params[i], 1, ft_strlen(e->params[i]) - 2);
			free(e->params[i]);
			e->params[i] = tmp;
		}
		i++;
	}
}

void	execute(t_data *e, char *abspath)
{
	struct stat	s;

	if (fork())
		e->pids++;
	else
	{
		if (abspath && execve(abspath, e->params, e->env) == -1)
			error_message(e, 4);
		else if (!ft_strcmp(e->params[0], ".") && !e->params[1])
			error_message(e, 3);
		else if ((!ft_strcmp(e->params[0], "..") && !e->params[1]) ||
		(e->params[0][0] == '.' && e->params[0][1] != '/'))
			error_message(e, 5);
		else if ((e->params[0][0] == '/' || e->params[0][0] == '.') &&
		stat(e->params[0], &s) != -1 && S_ISDIR(s.st_mode))
			error_message(e, 7);
		else if ((!abspath && e->params[0][0] != '.' && e->params[0][0] != '/'
		&& stat(e->params[0], &s) < 0))
			error_message(e, 5);
		else if (!abspath && execve(e->params[0], e->params, e->env) == -1)
			error_message(e, 4);
		exit(127);
	}
	abspath ? free(abspath) : 0;
}

void	init_execute(t_data *e)
{
	del_quotes(e);
	if (find_bin_paths(e) && e->params[0][0] != '/')
	{
		free_and_stuff(e, 6, 0);
		return ;
	}
	execute(e, construct_cmd_path(e));
	e->bins ? free_array(&e->bins) : 0;
}
