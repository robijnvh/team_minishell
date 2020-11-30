/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 14:12:16 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/30 11:01:40 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_alpha_no_num(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '?' || c == '!' || c == '@' || c == '#' || c == '*' || c == '$')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

char	*ft_strchr2(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str + 1);
		str++;
	}
	return (NULL);
}

int		ft_strlen2(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int		is_alpha_num(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '?' || c == '!' || c == '@' || c == '#' || c == '*' || c == '$')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	create_two_spaces(char **str)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(ft_strlen(*str) + 3);
	if (new == NULL)
		exit(1);
	new[0] = ' ';
	new[1] = ' ';
	while ((*str)[i])
	{
		new[i + 2] = (*str)[i];
		i++;
	}
	new[i + 2] = 0;
	*str = new;
}
