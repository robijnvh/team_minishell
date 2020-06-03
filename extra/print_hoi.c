/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_hoi.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 10:47:37 by Marty         #+#    #+#                 */
/*   Updated: 2020/05/27 12:49:00 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h> //
#include "minishell.h"

int		main(void)
{
	write(1, "hoi", 3);
	return (15);
}

	// parse_line(line, e);

	// // Split input
	// array = ft_split(line, ' ');

	// // Echo
	// if (!ft_strcmp(array[0], "echo"))
	// {
	// 	printf("%s\n", ft_strchr(line, ' ') + 1);
	// 	return (0);
	// }

	// // Setting command => array[0];
	// e->cmd = ft_strdup(array[i]);

	// // If array size == 1, no params are given so were done here;
	// if (get_array_size(array) == 1)
	// 	return (1);

	// // Making params array starting at array[1];
	// e->params = malloc(sizeof(char *) * get_array_size(array));
	// while (array[i + 1])
	// {
	// 	(e->params)[i] = ft_strdup(array[i + 1]);
	// 	i++;
	// }
	// (e->params)[i] = NULL;
	// free(array);
	// free(line);

	// // Returning number of params
