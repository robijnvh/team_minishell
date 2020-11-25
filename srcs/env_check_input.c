/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_check_input.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 11:16:56 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/25 10:51:05 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		print_array(char **array, int print, char div)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		if (print)
		{
			write(1, array[i], ft_strlen(array[i]));
			if (array[i + 1])
				write(1, &div, 1);
		}
		i++;
	}
	return (i);
}

int			check_input_cut(t_data *e, int j)
{
	int		i;
	char	c;

	i = 0;
	while (e->params[j][i] != '\0')
	{
		c = e->params[j][i];
		if (i == 0 && (c >= '0' && c <= '9'))
		{
			ft_printf(2, "bash: unset: `%s': not a valid identifier\n",
			e->params[j]);
			return (0);
		}
		if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9')))
			return (0);
		i++;
	}
	return (1);
}

void		move(char **order, int *i, int move)
{
	char	*tmp;

	if (move == 1)
	{
		while (order[*i][0] > order[*i + 1][0])
		{
			tmp = order[*i];
			order[*i] = order[*i + 1];
			order[*i + 1] = tmp;
			(*i)++;
			if (order[*i + 1] == 0)
				break ;
		}
		(*i) = 0;
		return ;
	}
	while (order[*i][move] == order[*i + 1][move] && order[*i][move] != 0)
		move++;
	if (order[*i][move] > order[*i + 1][move])
	{
		tmp = order[*i];
		order[*i] = order[*i + 1];
		order[*i + 1] = tmp;
	}
	(*i)++;
}

char		**make_cpy(t_data *e, char **env)
{
	char	**order;
	int		i;

	i = 0;
	while (env[i])
		i++;
	order = malloc(sizeof(char *) * (i + 1));
	!order ? free_and_stuff(e, 1, 1) : 0;
	order[i] = 0;
	i = 0;
	while (env[i])
	{
		order[i] = ft_strdup(env[i]);
		!order[i] ? free_and_stuff(e, 1, 1) : 0;
		i++;
	}
	return (order);
}

int			exp_no_params(t_data *e)
{
	int		i;
	char	**order;

	i = 0;
	order = make_cpy(e, e->env);
	while (order[i + 1])
	{
		if (order[i][0] > order[i + 1][0])
			move(order, &i, 1);
		else if (order[i][0] == order[i + 1][0])
			move(order, &i, 0);
		else
			i++;
	}
	i = 0;
	while (order[i])
	{
		ft_printf(1, "declare -x ");
		ft_putstr_exp(order[i]);
		ft_printf(1, "\n");
		i++;
	}
	free_array(&order);
	return (0);
}
