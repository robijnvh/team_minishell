/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 12:55:14 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/11/25 10:52:15 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		outer_quote(char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return ('\'');
		if (*s == '\"')
			return ('\"');
		s++;
	}
	return (0);
}

int		count_quote(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

int		check_quote(char *str, int i, int s, int d)
{
	int o;

	o = outer_quote(str);
	if (str[i] == '\"' && d % 2 == 0 &&
	count_quote(str, str[i]) % 2 == 0 && o != '\'')
		return (0);
	if (str[i] == '\'' && s % 2 == 0 &&
	count_quote(str, str[i]) % 2 == 0 && o != '\"')
		return (0);
	if (str[i] == '\\' && o == '\"' && str[i + 1] && is_alpha_num(str[i + 1]))
		write(1, "\\", 1);
	if (str[i] == '\\' && o == '\'')
		write(1, "\\", 1);
	return (1);
}

void	ft_putstr_exp(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		ft_putchar(s[i]);
		i++;
	}
	if (s[i] != '=')
		return ;
	ft_putchar(s[i]);
	i++;
	ft_putchar('\"');
	while (s[i] != '\0')
	{
		if (check_quote(s, i, count_chars(s, '\'', '\"'),
		count_chars(s, '\"', '\'')) == 1)
			ft_putchar(s[i]);
		i++;
	}
	ft_putchar('\"');
}

void	ft_putstr_no_quotes(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\'' && s[i] != '\"')
			ft_putchar(s[i]);
		i++;
	}
}
