/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 11:11:16 by Marty         #+#    #+#                 */
/*   Updated: 2020/12/02 10:48:06 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_for_env(t_data *e, int j)
{
	int	i;
	int	i2;

	i = 0;
	while (e->env[i] != NULL)
	{
		i2 = 0;
		if (e->env[i][i2] == e->params[j][i2 + 1] &&
		e->env[i][i2] != '=' && e->env[i][i2] != '\0')
		{
			while (e->env[i][i2] == e->params[j][i2 + 1] &&
			e->env[i][i2] != '=' && e->env[i][i2] != '\0')
				i2++;
			if (e->env[i][i2] == '=' || e->env[i][i2] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	export_env_var3(t_data *e, int j, int k)
{
	char	*tmp;
	char	*src1;
	char	*src2;
	int		i;

	i = 0;
	while (e->params[j][i] && e->params[j][i] != '=')
		i++;
	src1 = ft_substr(e->params[j], 0, i);
	src1 ? 0 : free_and_stuff(e, 0, 1);
	i = 0;
	while (e->env[k][i] && e->env[k][i] != '=')
		i++;
	src2 = ft_substr(e->env[k], i, ft_strlen(e->env[k]));
	src2 ? 0 : free_and_stuff(e, 0, 1);
	tmp = e->params[j];
	e->params[j] = ft_strjoin(src1, src2);
	e->params[j] ? 0 : free_and_stuff(e, 0, 1);
	free(tmp);
	free(src1);
	free(src2);
}

void	export_env_var2(t_data *e, int j, int start)
{
	int k;
	int l;
	int i;

	k = 0;
	while (e->env[k] != NULL)
	{
		l = 0;
		i = start;
		while (e->env[k][l] && e->env[k][l] != '=')
		{
			if (e->env[k][l] != e->params[j][i])
				break ;
			l++;
			i++;
		}
		if (e->env[k][l] == '=')
			export_env_var3(e, j, k);
		k++;
	}
}

void	export_env_var(t_data *e, int j)
{
	int i;

	i = 0;
	while (e->params[j][i] && e->params[j][i] != '=')
		i++;
	if (e->params[j][i] != '=')
		return ;
	i += 2;
	if (e->params[j][i] == '$')
		i++;
	export_env_var2(e, j, i);
}
