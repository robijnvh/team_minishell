/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 11:53:33 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/23 15:21:15 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_exit_param(t_data *e)
{
	int i;

	i = 0;
	while (e->params[1][i] != '\0')
	{
		if (!(e->params[1][i] >= '0' && e->params[1][i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	run_exit(t_data *e)
{
	int ex;

	if (!e->params[1] || (!ft_strcmp(e->params[1], "$?") && !e->params[2]))
		free_and_stuff(e, 8, 2);
	else if (!ft_strcmp(e->params[1], "$?") && e->params[2])
		free_and_stuff(e, 9, 0);
	else if (e->params[1] && is_alpha_no_num(e->params[1][0]))
		free_and_stuff(e, 10, 2);
	else if (e->params[1] && !is_alpha_no_num(e->params[1][0]) && !e->params[2])
	{
		ex = ft_atoi(e->params[1]);
		free_and_stuff(e, 8, 0);
		exit(ex);
	}
	else
		free_and_stuff(e, 9, 0);
}
