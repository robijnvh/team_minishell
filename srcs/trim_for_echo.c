/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_for_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 14:06:40 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/24 16:38:52 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_trim_check(char **args, int i)
{
	if ((ft_strncmp(args[i], "<", 2) != 0 && ft_strncmp(args[i], ">", 2) &&
	ft_strncmp(args[i], ">>", 3) != 0) && (i == 0 ||
	(ft_strncmp(args[i - 1], "<", 2) != 0 && ft_strncmp(args[i - 1], ">", 2)
	&& ft_strncmp(args[i - 1], ">>", 3) != 0)))
		return (1);
	else
		return (0);
}

char	**trimloop(char **args, char **out)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (ft_trim_check(args, i) == 1)
		{
			out[len] = ft_strdup(args[i]);
			if (out[len] == NULL)
			{
				free_array(&out);
				return ((char**)NULL);
			}
			len++;
		}
		i++;
	}
	return (out);
}

char	**ft_trim_args(char **args)
{
	int		i;
	int		len;
	char	**out;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (ft_trim_check(args, i) == 1)
			len++;
		i++;
	}
	i = 0;
	out = ft_calloc(len + 1, sizeof(char*));
	if (out == NULL)
		return (out);
	return (trimloop(args, out));
}
