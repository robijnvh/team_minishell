/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 15:41:35 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/03 15:41:44 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		display_env(t_data *e)
{
	int i;

	if (e->params[e->i])
	{
		write(1, "Error: No arguments allowed\n", 28);
		return (0);
	}
	i = 0;
	while (e->env[i] != NULL)
	{
		if (check_string(e->env[i]))
		{
			ft_putstr(e->env[i]);
			ft_putstr("\n");
		}
		i++;
	}
	return (1);
}

void	find_replace_line(t_data *e, int j)
{
	int		i;
	char	*tmp;

	i = 0;
	while (e->env[i] != NULL)
	{
		if (!ft_strcmp_env(e->env[i], e->params[e->i][j],
		ft_strlen(e->params[e->i][j])))
		{
			while (e->env[i] != NULL)
			{
				tmp = e->env[i];
				e->env[i] = e->env[i + 1];
				free(tmp);
				i++;
			}
			e->env[i] = NULL;
		}
		i++;
	}
}

int		cut_env(t_data *e)
{
	int		j;

	if (!check_input_cut(e))
		return (0);
	j = 0;
	while (e->params[e->i][j] != NULL)
	{
		find_replace_line(e, j);
		j++;
	}
	return (1);
}

void	init_env(char **envp, t_data *e)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i] != NULL)
		i++;
	(e->env) = (char **)ft_memalloc(sizeof(char*) * i);
	i = 0;
	while (envp[i] != NULL)
	{
		e->env[i] = (char *)ft_memalloc(PATH_MAX + 1);
		j = -1;
		while (envp[i][++j])
			e->env[i][j] = envp[i][j];
		e->env[i][j] = 0;
		i++;
	}
	e->env[i] = NULL;
	return ;
}
