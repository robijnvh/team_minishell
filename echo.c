/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/10 10:17:57 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/06/03 11:09:48 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		ft_my_strchr(const char *s)
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

char		*parse_env(t_data *e, char *name)
{
	int			i;
	int			j;
	char		**split;
	char		*tmp;

	i = 0;
	j = 0;
	while (e->env[i] != NULL)
	{
		if (!ft_strcmp_env(e->env[i], name, ft_strlen(name)))
		{
			split = ft_split(e->env[i], '=');
			tmp = ft_strdup(split[1]);
			free_array(split, 0);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

int			check_env_echo(char *cmnd, t_data *e)
{
	char *tmp;

	if (cmnd[0] == '$')
	{
		if ((tmp = parse_env(e, &cmnd[1])))
		{
			ft_putstr(tmp);
			free(tmp);
		}
		return (1);
	}
	return (0);
}

/**
 * echo
 */
// int		echo(t_data *e)
// {
// 	if (!ft_strcmp(e->params[e->i][0], "$?"))
// 		(e->params)[e->i][0] = ft_itoa(e->ret);
// 	print_array(e, e->params[e->i], 1, ' ');
// 	if (!e->wtf[e->i])
// 		write(1, "\n", 1);
// 	return (0);
// }

void		run_echo(t_data *e)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	c = 0;
	while (e->params[e->i][i] != NULL)
	{
		if (!check_env_echo(e->params[e->i][i], e))
		{
			if (!c)
				c = ft_my_strchr(e->params[e->i][i]);
			j = 0;
			while (e->params[e->i][i][j] != '\0')
			{
				if (e->params[e->i][i][j] != c)
					write(STDOUT_FILENO, e->params[e->i][i] + j, 1);
				j++;
			}
		}
		if (e->params[e->i][i] != NULL)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
