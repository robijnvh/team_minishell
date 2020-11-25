/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 15:41:35 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/25 13:19:01 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp_env(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] != '\0' && str2[i] != '\0' && (n > i))
	{
		ft_printf(1, "n: %i --- i: %i --- c1: %c --- c2: %c\n", n, i, str1[i], str2[i]);
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	ft_printf(1, "last: c1: %c --- c2: %c\n", str1[i], str2[i]);
	if (str1[i] == '=' || str1[i] == '\0')
		return (0);
	if (str1[i] != str2[i] && i != n)
		return (1);
	return (1);
}

int		display_env(t_data *e)
{
	int i;

	if (e->params[1])
	{
		ft_printf(2, "env: %s: No such file or directory\n", e->params[1]);
		errno ? free_and_stuff(e, 1, 0) : 0;
		return (0);
	}
	i = 0;
	while (e->env[i] != NULL)
	{
		if (check_string(e->env[i]))
		{
			ft_putstr_env(e->env[i], count_chars(e->env[i], '\'', '\"'),
			count_chars(e->env[i], '\"', '\''));
			ft_putstr("\n");
		}
		i++;
	}
	return (1);
}

void	find_replace_line(t_data *e, int j)
{
	int		i;
	char	*tmp;

	i = 0;
	while (e->env[i] != NULL)
	{
		if (!ft_strcmp_env(e->env[i], e->params[j],
		ft_strlen(e->params[j])))
		{
			tmp = e->env[i];
			while (e->env[i] != NULL)
			{
				e->env[i] = e->env[i + 1];
				i++;
			}
			free(tmp);
			e->env[i] = NULL;
		}
		i++;
	}
}

int		cut_env(t_data *e)
{
	int		j;

	if (!e->params[1])
		return (0);
	j = 1;
	while (e->params[j] != NULL)
	{
		if (check_input_cut(e, j))
			find_replace_line(e, j);
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
	errno ? free_and_stuff(e, 1, 1) : 0;
	i = 0;
	while (envp[i] != NULL)
	{
		e->env[i] = (char *)ft_memalloc(PATH_MAX + 1);
		errno ? free_and_stuff(e, 1, 1) : 0;
		j = 0;
		while (envp[i][j])
		{
			e->env[i][j] = envp[i][j];
			j++;
		}
		e->env[i][j] = 0;
		i++;
	}
	e->env[i] = NULL;
	return ;
}
