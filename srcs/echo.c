/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/10 10:17:57 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/12/02 10:47:26 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_ret(t_data *e)
{
	int i;

	i = 0;
	while (1)
	{
		i = index_off(e->params, "$?");
		if (i < 0)
			return ;
		else
		{
			free(e->params[i]);
			e->params[i] = ft_itoa(e->ret);
		}
	}
}

int		check_slash(char *str, int *index)
{
	int i;
	int ret;

	ret = 0;
	i = *index - 1;
	while (i >= 0)
	{
		if (str[i] != '\\')
			break ;
		ret++;
		i--;
	}
	return (ret % 2);
}

char	ft_my_strchr(const char *s)
{
	int				i;
	char			c;

	i = 0;
	while (s[i] != 34 && s[i] != 39)
	{
		if (!s[i])
			return (0);
		i++;
	}
	c = s[i];
	return (c);
}

int		run_echo(t_data *e)
{
	int		i;
	char	**args;

	args = ft_trim_args(e->params);
	args ? 0 : free_and_stuff(e, 0, 1);
	i = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
			i++;
	}
	while (args[i])
	{
		if (args[i] && !args[i + 1])
			write_echo(args[i], 0, e, 2);
		else
			write_echo(args[i], 1, e, 2);
		i++;
		if (args[i] != 0 && e->write != 0)
			ft_putchar_fd(' ', 1);
	}
	if (!args[1] || (args[1] && ft_strncmp(args[1], "-n", 3) != 0))
		ft_putchar_fd('\n', 1);
	free_array(&args);
	return (0);
}
