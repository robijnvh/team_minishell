/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_echo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 14:21:34 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/12/01 11:28:34 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quote(char *str, int *i, int fd)
{
	(*i)++;
	while (str[*i] != '\'')
	{
		write(fd, &str[*i], 1);
		(*i)++;
	}
}

int		search_env_var(char *str, int *i, t_data *e)
{
	int		j;
	int		l;
	char	**split;

	l = 0;
	j = 0;
	while (e->env[j])
	{
		while (e->env[j][l] == str[*i + l] && e->env[j][l])
			l++;
		if (e->env[j][l] == '=' && !is_alpha_num(str[*i + l]))
		{
			split = ft_split(e->env[j], '=');
			split ? 0 : free_and_stuff(e, 0, 1);
			ft_putstr_env(split[1], count_chars(split[1], '\'', '\"'),
			count_chars(split[1], '\"', '\''));
			e->write = 1;
			free_array(&split);
			return (1);
		}
		l = 0;
		j++;
	}
	return (0);
}

void	double_quote(char *str, int *i, int fd, t_data *e)
{
	(*i)++;
	while (!(str[*i] == '\"' && !check_slash(str, i)) && str[*i] != 0)
	{
		if (str[*i] == '$' && is_alpha_num(str[*i + 1]) &&
		!check_slash(str, i))
		{
			(*i)++;
			if (str[*i] == '?')
			{
				ft_putnbr_fd(0, fd);
				e->write = 1;
			}
			else
				search_env_var(str, i, e);
			while (is_alpha_num(str[*i]))
				(*i)++;
		}
		else
		{
			if (!(str[*i] == '\\' && !check_slash(str, i) && (str[*i + 1]
			== '\"' || str[*i + 1] == '\\')))
				e->write = write(fd, &str[*i], 1);
			(*i)++;
		}
	}
}

void	found_env(char *str, int fd, t_data *e, int *i)
{
	int ret;

	ret = -1;
	(*i)++;
	if (str[*i] == '?')
	{
		ft_putnbr_fd(0, fd);
		e->write = 1;
	}
	else
		ret = search_env_var(str, i, e);
	if (ret == 0 && !is_alpha_no_num(str[*i]))
		return ;
	while (is_alpha_num(str[*i]))
		(*i)++;
}

void	write_echo(char *str, int param, t_data *e, int i)
{
	create_two_spaces(&str);
	while (str[i])
	{
		if (str[i] == '\'' && !check_slash(str, &i))
			single_quote(str, &i, 1);
		else if (str[i] == '\"' && !check_slash(str, &i))
			double_quote(str, &i, 1, e);
		else if (str[i] == '$' && is_alpha_num(str[i + 1]) &&
		!check_slash(str, &i))
			found_env(str, 1, e, &i);
		else if (str[i] == '\\')
		{
			write_backslash(e, str, &i, param);
			continue ;
		}
		else if (!(str[i] == '\\' && !check_slash(str, &i) &&
		(str[i + 1] >= 32 && str[i + 1] <= 126)) &&
		!(str[i] == '$' && str[i + 1] && ft_isquote(str[i + 1])))
			e->write = write(1, &str[i], 1);
		if (str[i] != 0)
			i++;
	}
	free(str);
}
