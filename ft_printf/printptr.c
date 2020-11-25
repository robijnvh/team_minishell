/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printptr.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 15:26:40 by rvan-hou      #+#    #+#                 */
/*   Updated: 2019/12/12 15:26:41 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ptr_nbr_final(unsigned long hex, t_struct *flags, unsigned long tmp)
{
	if (flags->plus > 0 && flags->width == 0
	&& flags->precision == 0 && tmp >= 0)
		writechar('+', flags);
	if (hex >= 16)
	{
		ptr_nbr_final((hex / 16), flags, tmp);
		ptr_nbr_final((hex % 16), flags, tmp);
	}
	if (hex < 16)
	{
		if (flags->capital > 0)
			converthex_capitalx(hex, flags);
		else
			converthex_x(hex, flags);
	}
}

void	ptr_writeprefix(t_struct *flags)
{
	writechar('0', flags);
	writechar('x', flags);
}

void	ptr_precision(t_struct *flags, unsigned long ptr)
{
	int	check;

	check = 0;
	if (flags->precision > 0)
	{
		check = flags->precision - ptr_length(ptr);
		if (ptr == 0 && flags->precision != -1)
			check--;
		while (check > 0)
		{
			writechar('0', flags);
			check--;
		}
	}
	if (flags->precision != -1)
		ptr_nbr_final(ptr, flags, ptr);
}

void	ptr_width(t_struct *flags, unsigned long ptr)
{
	char			fill;
	int				check;

	fill = flags->zero ? '0' : ' ';
	check = flags->width - (ptr_length(ptr) + 2);
	if (ptr == 0 && flags->precision != -1)
		check--;
	if (flags->minus > 0)
	{
		ptr_writeprefix(flags);
		if (flags->precision != -1)
			ptr_precision(flags, ptr);
	}
	while (check > 0)
	{
		writechar(fill, flags);
		check--;
	}
	if (flags->minus == 0)
	{
		ptr_writeprefix(flags);
		if (flags->precision != -1)
			ptr_precision(flags, ptr);
	}
}

void	printptr(va_list ap, t_struct *flags)
{
	unsigned long	ptr;

	ptr = va_arg(ap, unsigned long);
	if (!ptr)
		ptr = 0;
	if (flags->width > 0)
		ptr_width(flags, ptr);
	else
	{
		ptr_writeprefix(flags);
		ptr_precision(flags, ptr);
	}
}
