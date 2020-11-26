/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 15:16:09 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/26 13:49:34 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_bin_paths(t_data *e)
{
	char	*paths;
	int		i;

	i = 0;
	paths = NULL;
	while (e->env[i])
	{
		paths = ft_strnstr(e->env[i], "PATH", 4);
		if (paths)
			break ;
		i++;
	}
	if (!paths)
		return (1);
	e->bins = ft_split(paths + 5, ':');
	errno ? free_and_stuff(e, 1, 0) : 0;
	if (!e->bins)
		return (1);
	return (0);
}

int		ft_strcmp_cmd(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && ((s1[i] == s2[i]) || (s1[i] == s2[i] - 32)))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	values(t_data *e, int wait)
{
	if (WIFEXITED(wait))
		e->ret = WEXITSTATUS(wait);
	if (WIFSIGNALED(wait))
	{
		e->ret = WTERMSIG(wait);
		if (e->ret == 2)
		{
			e->ret = 130;
			e->is_child = 1;
		}
		if (e->ret == 3)
		{
			e->ret = 131;
			e->is_child = 2;
		}
	}
}

void	return_values(t_data *e)
{
	int x;
	int wait;

	wait = 0;
	x = 0;
	while (x < e->pids)
	{
		waitpid(-1, &wait, 0);
		values(e, wait);
		x++;
	}
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
