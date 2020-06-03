/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_count.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/30 09:55:02 by Marty         #+#    #+#                 */
/*   Updated: 2020/05/30 10:01:42 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
	// int ret;
	// char buf[100];
	// char **array;
	// int count;

	// read(0, &buf, 100);
	// buf[ret] = '\0';
	// array = ft_split(buf, ' ');
	// count = cnt_prnt_array(array, 0, 0);
	// printf("count: %d\n", count);

	int count;

	count = cnt_prnt_array(argv, 1, '\n');
	printf("count: %d\n", count);
	
	return (0);
}