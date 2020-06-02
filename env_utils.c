/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 15:23:43 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/06/02 13:40:17 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char			**free_machine(char **str, int i)
// {
// 	while (str)
// 	{
// 		free((void *)&str[i]);
// 		i--;
// 	}
// 	free(str);
// 	return (NULL);
// }

int		check_char(char c)
{
	if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
	|| (c >= '0' && c <= '9')))
		return (0);
	return (1);
}

void	free_test(char **str)
{
	int i;
	int	n;

	i = 0;
	while (str[i] != NULL)
		i++;
	n = i;
	i = 0;
	// printf("check1\n");
	while (i < n - 1)
	{
		printf("i: %i\n", i);
		// printf("str: %s\n", str[i]);
		if (str[i])
			free(str[i]);
		i++;
	}
	// printf("check2\n");
	free(str);
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
	return (0);
}
