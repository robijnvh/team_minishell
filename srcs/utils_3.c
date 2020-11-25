/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 15:16:09 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/24 16:39:42 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_bin_paths(t_data *e)
{
	char	*paths;
	int		i;

	i = 0;
	paths = NULL;
	while (e->env[i])
	{
		paths = ft_strnstr(e->env[i], "PATH", 4);
		if (paths)
			break ;
		i++;
	}
	if (!paths)
		return (1);
	e->bins = ft_split(paths + 5, ':');
	errno ? free_and_stuff(e, 1, 0) : 0;
	if (!e->bins)
		return (1);
	return (0);
}

int		ft_strcmp_cmd(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && ((s1[i] == s2[i]) || (s1[i] == s2[i] - 32)))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
