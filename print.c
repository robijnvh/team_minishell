/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 10:08:15 by Marty         #+#    #+#                 */
/*   Updated: 2020/05/19 15:02:28 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char *argv[])
{
	cnt_prnt_array(argv, 1, '\n');
	return (5);
}