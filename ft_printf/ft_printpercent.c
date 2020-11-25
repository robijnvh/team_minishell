/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printpercent.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 12:33:40 by rvan-hou      #+#    #+#                 */
/*   Updated: 2019/12/12 12:33:41 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	printpercent(t_struct *flags)
{
	int		check;
	char	fill;

	fill = ' ';
	check = 0;
	if (flags->width > 0)
		check = flags->width - 1;
	if (flags->minus > 0)
		writechar('%', flags);
	while (check > 0)
	{
		if (flags->zero > 0 && flags->minus == 0)
			fill = '0';
		writechar(fill, flags);
		check--;
	}
	if (flags->minus == 0)
		writechar('%', flags);
}
