/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printhex_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 15:20:22 by rvan-hou      #+#    #+#                 */
/*   Updated: 2019/12/13 15:20:23 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	converthex_x(unsigned int res, t_struct *flags)
{
	char	conv;

	if (res >= 0 && res <= 9)
		conv = res + 48;
	if (res == 10)
		conv = 'a';
	if (res == 11)
		conv = 'b';
	if (res == 12)
		conv = 'c';
	if (res == 13)
		conv = 'd';
	if (res == 14)
		conv = 'e';
	if (res == 15)
		conv = 'f';
	writechar(conv, flags);
}

void	converthex_capitalx(unsigned int res, t_struct *flags)
{
	char	conv;

	if (res >= 0 && res <= 9)
		conv = res + 48;
	if (res == 10)
		conv = 'A';
	if (res == 11)
		conv = 'B';
	if (res == 12)
		conv = 'C';
	if (res == 13)
		conv = 'D';
	if (res == 14)
		conv = 'E';
	if (res == 15)
		conv = 'F';
	writechar(conv, flags);
}

int		hex_length(unsigned int hex)
{
	int		ret;

	ret = 0;
	while (hex)
	{
		hex = hex / 16;
		ret++;
	}
	return (ret);
}

int		hex_getcountp(t_struct *flags, unsigned int hex,
		unsigned int tmp)
{
	int		ret;

	ret = flags->precision;
	if (flags->precision == -1)
		return (0);
	if (flags->precision <= hex_length(hex))
		ret = hex_length(hex);
	if (tmp < 0)
		ret++;
	if (flags->plus > 0 && tmp >= 0)
		ret++;
	if (flags->hash > 0 && tmp != 0)
		ret = ret + 2;
	return (ret);
}

void	writeprefix(unsigned int hex, t_struct *flags)
{
	if (flags->hash > 0 && hex != 0)
	{
		writechar('0', flags);
		if (flags->capital > 0)
			writechar('X', flags);
		else
			writechar('x', flags);
	}
}
