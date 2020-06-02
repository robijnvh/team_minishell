/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:37:31 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/02 10:53:10 by rvan-hou      ########   odam.nl         */
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

// char	**fill_cpy(t_data *e, int i, int array_cnt, int i3)
// {
// 	int		i2;
// 	int		j;
// 	char	**tmp;

// 	if (i == (array_cnt - 1))
// 	{
// 		i2 = 0;
// 		while (e->params[e->i][i2] != NULL)
// 		{
// 			tmp[i] = (char *)ft_memalloc(PATH_MAX + 1);
// 			j = 0;
// 			while (e->params[e->i][i2][j] != '\0')
// 			{
// 				tmp[i][j] = e->params[e->i][i2][j];
// 				j++;
// 			}
// 			tmp[i][j] = 0;
// 			i2++;
// 			i++;
// 		}
// 	}
// 	tmp[i] = (char *)ft_memalloc(PATH_MAX + 1);
// 	j = 0;
// 	while (e->env[i3][j] != '\0')
// 	{
// 		tmp[i][j] = e->env[i3][j];
// 		j++;
// 	}
// 	tmp[i][j] = 0;
// 	return (tmp);
// }

int		add_env(t_data *e)
{
	char	**tmp;
	int		i;
	int		i2;
	int		i3;
	int		j;
	int		array_cnt;
	int		param_cnt;

	if (!check_input_add(e))
		return (0);
	array_cnt = cnt_prnt_array(e->env, 0, 0);
	param_cnt = cnt_prnt_array(e->params[e->i], 0, 0);
	tmp = (char **)ft_memalloc(sizeof(char*) * (array_cnt + param_cnt + 1));
	i = 0;
	i3 = 0;
	while (i < (array_cnt + param_cnt))
	{
		// tmp = fill_cpy(e, i, array_cnt, i3);
		if (i == (array_cnt - 1))
		{
			i2 = 0;
			while (e->params[e->i][i2] != NULL)
			{
				tmp[i] = (char *)ft_memalloc(PATH_MAX + 1);
				j = 0;
				while (e->params[e->i][i2][j] != '\0')
				{
					tmp[i][j] = e->params[e->i][i2][j];
					j++;
				}
				tmp[i][j] = 0;
				i2++;
				i++;
			}
		}
		tmp[i] = (char *)ft_memalloc(PATH_MAX + 1);
		j = 0;
		while (e->env[i3][j] != '\0')
		{
			tmp[i][j] = e->env[i3][j];
			j++;
		}
		tmp[i][j] = 0;
		i++;
		i3++;
	}
	tmp[i] = NULL;
	free_test(e->env);
	e->env = tmp;
	return (1);
}

int		cut_env(t_data *e)
{
	int i;
	int	j;

	if (!check_input_cut(e))
		return (0);
	i = 0;
	j = 0;
	while (e->params[e->i][j] != NULL)
	{
		while (e->env[i] != NULL)
		{
			if (!ft_strcmp_env(e->env[i], e->params[e->i][j],
			ft_strlen(e->params[e->i][j])))
			{
				while (i < cnt_prnt_array(e->env, 0, 0))
				{
					free(e->env[i]);
					e->env[i] = e->env[i + 1];
					i++;
				}
				e->env[i] = NULL;
			}
			i++;
		}
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
