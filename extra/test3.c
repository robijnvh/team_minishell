/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 17:01:46 by Marty         #+#    #+#                 */
/*   Updated: 2020/05/04 17:09:02 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

int main(void)
{
	DIR *dir;
	struct dirent *sd;

	dir = opendir(".");
	sd = readdir(dir);
	while (sd)
	{
		printf(">> %s\n", sd->d_name);
		sd = readdir(dir);
	}
	return (0);
}