/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_check_input.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 13:01:43 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/06/03 14:16:21 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_input_cut(t_data *e)
{
	int i;
	int	j;

	if (!e->params[e->i])
		return (0);
	j = 0;
	while (e->params[e->i][j] != NULL)
	{
		i = 0;
		if (!ft_strcmp(e->params[e->i][j], "PWD"))
		{
			write(1, "You can't do that\n", 18);
			return (0);
		}
		while (e->params[e->i][j][i] != '\0')
		{
			if (!check_char(e->params[e->i][j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

char	**ft_sort(char **order, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp_exp(order[i], order[j]) > 0)
			{
				tmp = order[i];
				order[i] = order[j];
				order[j] = tmp;
			}
			j++;
		}
		i++;
	}
	free(tmp);
	return (order);
}

void	free_tmp(char **tmp, int n)
{
	int i;

	i = 0;
	while (i < n - 1)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

int		exp_no_params(t_data *e)
{
	int		i;
	int		n;
	char	**order;
	char	**tmp;

	i = 0;
	n = print_array(e, e->env, 0, '\0');
	tmp = (char**)malloc(sizeof(char *) * n);
	while (i < n)
	{
		tmp[i] = ft_strdup(e->env[i]);
		i++;
	}
	order = ft_sort(tmp, n);
	i = 0;
	while (i < n)
	{
		ft_putstr("declare -x ");
		ft_putstr_exp(order[i]);
		ft_putstr("\n");
		i++;
	}
	free_tmp(tmp, n);
	return (0);
}

int		check_input_add(t_data *e)
{
	int	i;
	int	j;

	if (!e->params[e->i])
		return (exp_no_params(e));
	j = 0;
	while (e->params[e->i][j] != NULL)
	{
		i = 0;
		while (e->env[i] != NULL)
		{
			if (!ft_strcmp(e->params[e->i][j], e->env[i]))
				return (0);
			i++;
		}
		while (e->params[e->i][j][i] != '=' && e->params[e->i][j][i] != '\0')
		{
			if (!check_char(e->params[e->i][j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}
