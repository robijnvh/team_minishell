/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:16:19 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/02 14:07:53 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cd(t_data *e)
{
	char buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	e->og_path = ft_strdup(buf);
}

char	*trim(char *str, int c)
{
	int		i;
	int		ret;
	int		count;
	char	*trim;

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

void	change_dir(t_data *e)
{
	char	*tmp;
	
	if (!e->params[e->i])
	{
		e->path = e->og_path;
		chdir(e->og_path);
		return ;
	}
	getcwd(e->buf, PATH_MAX);
	if (!ft_strcmp(e->params[e->i][e->j], ".."))
		e->path = trim(e->buf, '/');
	else if (e->params[e->i][e->j][0] != '/')
	{
		e->path = ft_strjoin("/", e->params[e->i][e->j]);
		tmp = e->path;
		e->path = ft_strjoin(e->buf, e->path);
		free(tmp);
	}
	else
		e->path = ft_strjoin(e->buf, e->params[e->i][e->j]);
	if (chdir(e->path) == -1 && chdir(e->params[e->i][e->j]) == -1)
	{
		printf("%s: No such file or directory\n", e->params[e->i][e->j]);
		e->ret = 1;
	}
	free(e->path);
}

void	list_dir(t_data *e)
{
	DIR				*dir;
	struct dirent	*sd;

	dir = opendir(".");
	sd = malloc(sizeof(sd));
	while (sd)
	{
		sd = readdir(dir);
		if (sd)
		{
			if (e->wtf[e->i])
				wtf(e, sd->d_name, -1);
			else
				printf("- %s\n", sd->d_name);
		}
	}
	closedir(dir);
	free(sd);
}

void	get_path(t_data *e)
{
	char buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (e->wtf[e->i])
		wtf(e, buf, -1);
	else
		printf("%s\n", buf);
}
