/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 15:40:59 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/30 15:23:10 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_params(t_data *e, int j)
{
	int i;
	int	i2;

	i = 0;
	i2 = 0;
	while (e->params[j][i] != '=' && e->params[j][i] != '\0')
		i++;
	while (e->env[i2] != NULL)
	{
		if (!ft_strcmp_env(e->env[i2], e->params[j], i))
			return (0);
		i2++;
	}
	i = 0;
	if (!check_char(e->params[j][i], i, j, e))
		return (0);
	while (e->params[j][i] != '=' && e->params[j][i] != '\0')
	{
		if (!check_char(e->params[j][i], i, j, e))
			return (0);
		i++;
	}
	return (1);
}

char	**make_tmp(t_data *e, char **tmp, int i)
{
	int		i3;
	int		i2;

	i3 = 0;
	while (e->env[i3] != NULL)
	{
		if (i == (e->arr_cnt - 1))
		{
			i2 = 1;
			while (e->params[i2] != NULL)
			{
				if (check_params(e, i2))
				{
					tmp[i] = fill_str(e->params[i2], i2, e);
					i++;
				}
				i2++;
			}
		}
		tmp[i] = fill_str(e->env[i3], 0, e);
		i++;
		i3++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int		check_double(t_data *e, int i, int j)
{
	int	i2;
	int	check;

	i2 = 0;
	check = 0;
	while (e->params[j][i2] != '=' && e->params[j][i2] != '\0')
		i2++;
	if (e->params[j][i2] != '=')
		check = 1;
	if (!ft_strcmp_env(e->env[i], e->params[j], i2))
	{
		if (check == 1)
			return (0);
		free(e->env[i]);
		e->env[i] = ft_strdup(e->params[j]);
		e->env[i] ? 0 : free_and_stuff(e, 0, 1);
		return (1);
	}
	return (1);
}

int		check_input_add(t_data *e)
{
	int	i;
	int	j;

	j = 1;
	while (e->params[j] != NULL)
	{
		i = 0;
		while (e->env[i] != NULL)
		{
			if (!check_double(e, i, j))
				return (0);
			i++;
		}
		i = 0;
		while (e->params[j][i] && e->params[j][i] != '=')
			i++;
		if (e->params[j][i] == '=' && (e->params[j][i + 1] &&
		(e->params[j][i + 1] == '$' || (e->params[j][i + 1] == '\"' &&
		e->params[j][i + 2] && e->params[j][i + 2] == '$'))))
			export_env_var(e, j);
		j++;
	}
	return (1);
}

int		add_env(t_data *e)
{
	char	**tmp;

	if (!e->params[1])
		return (exp_no_params(e));
	check_for_env_vars(e);
	if (!check_input_add(e))
		return (0);
	e->arr_cnt = print_array(e->env, 0, '\0');
	e->par_cnt = print_array(e->params, 0, '\0');
	tmp = (char **)ft_memalloc(sizeof(char*) * (e->arr_cnt + e->par_cnt + 1));
	tmp ? 0 : free_and_stuff(e, 0, 1);
	tmp = make_tmp(e, tmp, 0);
	if (!tmp)
		return (0);
	free_array(&e->env);
	e->env = tmp;
	return (1);
}
