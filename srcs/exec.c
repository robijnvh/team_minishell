/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:13:11 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/12/02 10:41:09 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_cmd_in_bin(t_data *e, char **bins, char *cmd, int i)
{
	DIR				*dir;
	struct dirent	*sd;

	while (bins[i])
	{
		errno = 0;
		dir = opendir(bins[i]);
		while (!errno)
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
		if (dir)
			closedir(dir) < 0 ? free_and_stuff(e, 1, 1) : 0;
		i++;
	}
	return (-1);
}

void	handle_dir_spaces(t_data *e)
{
	int		i;
	char	*tmp;

	i = 0;
	while (e->params && e->params[i])
	{
		if (e->params[0][ft_strlen(e->params[0]) - 1] == '\\' && e->params[i])
		{
			tmp = e->params[0];
			e->params[0] = ft_substr(tmp, 0, ft_strlen(e->params[0]) - 1);
			free(tmp);
			tmp = e->params[0];
			e->params[0] = ft_strjoin3(tmp, " ", e->params[i]);
			free(tmp);
		}
		i++;
	}
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
	i = find_cmd_in_bin(e, e->bins, e->params[0], 0);
	if (i < 0)
		return (NULL);
	return (ft_strjoin3(e->bins[i], "/", e->params[0]));
}

void	execute(t_data *e, char *abspath)
{
	struct stat	s;

	if (fork())
		e->pids++;
	else
	{
		if (!abspath && !ft_strcmp(e->params[0], ".") && !e->params[1])
			error_message(e, 3);
		else if (!abspath && ((!ft_strcmp(e->params[0], "..") &&
		!e->params[1]) || (e->params[0][0] == '.' && e->params[0][1] != '/')))
			error_message(e, 5);
		else if (abspath && execve(abspath, e->params, e->env) == -1)
			error_message(e, 4);
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
	handle_dir_spaces(e);
	if (!ft_strcmp(e->params[0], ".") || !ft_strcmp(e->params[0], ".."))
		execute(e, NULL);
	else
		execute(e, construct_cmd_path(e));
	e->bins ? free_array(&e->bins) : 0;
}
