/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   improve_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 13:29:38 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/26 11:04:31 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_strnstr(char *str, char *insert, int place)
{
	char *tmp;
	char *sub1;
	char *sub2;

	if (!str || !insert)
		return (NULL);
	sub1 = ft_substr(str, 0, place);
	sub2 = ft_strjoin(sub1, insert);
	free(sub1);
	sub1 = ft_substr(str, place, ft_strlen(str) - place);
	if (!sub1 || !sub2)
		return (NULL);
	tmp = ft_strjoin(sub2, sub1);
	free(sub1);
	free(sub2);
	free(str);
	return (tmp);
}

int		check_redirect(t_data *e, int *i)
{
	if (e->line[*i] == e->line[*i + 1] && e->line[*i] == e->line[*i + 2])
	{
		return (ft_printf(2,
		"minishell: syntax error near unexpected token `%c'\n",
		e->line[*i]));
	}
	if (e->line[*i - 1] != ' ')
		e->line = insert_strnstr(e->line, " ", *i);
	if (e->line[*i] == e->line[*i + 1])
		(*i)++;
	if (e->line[*i + 1] != ' ')
		e->line = insert_strnstr(e->line, " ", *i + 1);
	return (0);
}

int		count_chars(char *str, char a, char b)
{
	int i;
	int count;
	int closed;

	i = 0;
	count = 0;
	closed = 0;
	while (str[i])
	{
		if (b == '"' && str[i] == b && count % 2 == 0 &&
		!check_slash(str, &i))
			closed++;
		else if (b == '\'' && str[i] == b && count % 2 == 0)
			closed++;
		if (a == '"' && str[i] == a && closed % 2 == 0 &&
		!check_slash(str, &i))
			count++;
		else if (a == '\'' && str[i] == a && closed % 2 == 0)
			count++;
		i++;
	}
	return (count);
}

int		improve_line(t_data *e)
{
	int i;

	i = 0;
	if (count_chars(e->line, '\'', '\"') % 2)
	{
		write(2, "minishell: ('): Not closed\n", 27);
		return (1);
	}
	if (count_chars(e->line, '\"', '\'') % 2)
	{
		write(2, "minishell: (\"): Not closed\n", 27);
		return (1);
	}
	while (e->line[i])
	{
		if (e->line[i] == '|' && e->line[i - 1] != ' ')
			e->line = insert_strnstr(e->line, " ", i);
		if (e->line[i] == '|' && e->line[i + 1] != ' ')
			e->line = insert_strnstr(e->line, " ", i + 1);
		if (e->line[i] == '<' || e->line[i] == '>')
			if (check_redirect(e, &i))
				return (1);
		i++;
	}
	return (0);
}
