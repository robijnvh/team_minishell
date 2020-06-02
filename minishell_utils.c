/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:25:01 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/02 17:53:30 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				index_off(char **array, char *str)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], str))
			return (i);
		i++;
	}
	return (-1);
}

size_t			print_array(t_data *e, char **array, int print, char div)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		if (print)
		{
			if (e->wtf[e->i])
				wtf(e, array[i], i);
			else
			{
				write(1, array[i], ft_strlen(array[i]));
				if (array[i + 1])
					write(1, &div, 1);
			}
		}
		i++;
	}
	return (i);
}

void			prompt(t_data *e)
{
	if (!e->first)
		e->first = write(1, " \e[1;1H\e[2J", 12);
	write(1, "$> ", 3);
}

void			free_array(char **array, int size)
{
	int i;

	i = 0;
	if (!array)
		return ;
	if (size)
		while (size >= 0)
		{
			size--;
			free(array[size]);
		}
	else
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
	array ? free(array) : 0;
}
