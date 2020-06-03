/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 15:40:59 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/03 15:41:53 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_str(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)ft_memalloc(PATH_MAX + 1);
	while (str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	**make_tmp(t_data *e, char **tmp)
{
	int		i;
	int		i3;
	int		i2;

	i = 0;
	i3 = 0;
	while (i < (e->arr_cnt + e->par_cnt))
	{
		if (i == (e->arr_cnt - 1))
		{
			i2 = 0;
			while (e->params[e->i][i2] != NULL)
			{
				tmp[i] = fill_str(e->params[e->i][i2]);
				i2++;
				i++;
			}
		}
		tmp[i] = fill_str(e->env[i3]);
		i++;
		i3++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int		add_env(t_data *e)
{
	char	**tmp;
	int		i;
	int		i2;
	int		i3;

	if (!check_input_add(e))
		return (0);
	e->arr_cnt = print_array(e, e->env, 0, '\0');
	e->par_cnt = print_array(e, e->params[e->i], 0, '\0');
	tmp = (char **)ft_memalloc(sizeof(char*) * (e->arr_cnt + e->par_cnt + 1));
	tmp = make_tmp(e, tmp);
	free_array(e->env, 0);
	e->env = tmp;
	return (1);
}
