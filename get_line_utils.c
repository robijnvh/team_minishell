/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_line_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 15:44:17 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/03 15:45:44 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr2(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (str + 1);
		str++;
	}
	return (0);
}

int		ft_strlen2(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\0')
		i++;
	return (i);
}
