/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 10:43:24 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/11/26 14:06:59 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_path(t_data *e, char *str)
{
	int		i;
	char	*tmp;
	char	*src;

	i = 0;
	tmp = NULL;
	while (e->env[i])
	{
		if (!ft_strncmp(e->env[i], "PWD", 3))
		{
			tmp = e->env[i];
			src = ft_substr(e->env[i], 0, 4);
			src ? 0 : free_and_stuff(e, 0, 1);
			free(tmp);
			tmp = src;
			e->env[i] = ft_strjoin(src, str);
			e->env[i] ? 0 : free_and_stuff(e, 0, 1);
			free(src);
		}
		i++;
	}
}

int		check_cd_arg(t_data *e, int i)
{
	char	*tmp;

	tmp = NULL;
	tmp = e->path;
	if (check_spaces_in_path(e, i, 0) &&
	!(chdir(e->path) == -1 && chdir(e->params[i]) == -1))
	{
		free_and_zero(&e->path);
		return (0);
	}
	if (e->params[i][0] == '~')
		return (only_cd(e, 3));
	else if (!ft_strcmp(e->params[i], ".."))
		e->path = trim(e->buf, '/');
	else if (e->params[i][0] != '/')
		e->path = ft_strjoin3(e->buf, "/", e->params[i]);
	else if (!ft_strncmp(e->params[i], e->og_path, 6))
		e->path = ft_strdup(e->params[i]);
	else
		e->path = ft_strjoin(e->buf, e->params[i]);
	tmp ? free(tmp) : 0;
	e->path ? 0 : free_and_stuff(e, 0, 1);
	return (1);
}

int		wrong_cd_arg(t_data *e, int i, int *check)
{
	if (e->params[i][0] != '$' && *check == 0)
	{
		ft_printf(2, "minishell: cd: %s: %s\n", e->params[1], strerror(errno));
		return (0);
	}
	else
		only_cd(e, 3);
	e->ret = 1;
	*check = 0;
	return (1);
}
