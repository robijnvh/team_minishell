/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 15:23:43 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/06/03 14:57:38 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_char(char c)
{
	if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
	|| (c >= '0' && c <= '9')))
		return (0);
	return (1);
}

int		count_parameters(t_data *e)
{
	int index;

	index = 0;
	while (e->params[e->i][index] != NULL)
		index++;
	return (index);
}

int		check_string(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		ft_strcmp_env(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] != '\0') && str2[i] != '\0' && (n > i))
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (str1[i] == '=' || str1[i] == '\0')
		return (0);
	if (str1[i] != str2[i] && i != n)
		return (1);
	return (1);
}

int		ft_strcmp_exp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
