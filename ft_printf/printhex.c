/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printhex.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 15:54:48 by rvan-hou      #+#    #+#                 */
/*   Updated: 2019/12/12 15:54:49 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	nbr_final(unsigned int hex, t_struct *flags, unsigned int tmp)
{
	if (flags->plus > 0 && flags->width == 0
	&& flags->precision == 0 && tmp >= 0)
		writechar('+', flags);
	if (hex >= 16)
	{
		nbr_final((hex / 16), flags, tmp);
		nbr_final((hex % 16), flags, tmp);
	}
	if (hex < 16)
	{
		if (flags->capital > 0)
			converthex_capitalx(hex, flags);
		else
			converthex_x(hex, flags);
	}
}

void	hex_onlyprecision(t_struct *flags, unsigned int hex,
		unsigned int tmp)
{
	int		check;
	char	fill;

	fill = '0';
	check = flags->precision - hex_length(hex);
	if (flags->hash > 0 && hex != 0)
		writeprefix(hex, flags);
	if (flags->precision == -1)
	{
		if (tmp != 0)
			nbr_final(hex, flags, tmp);
		return ;
	}
	if (flags->precision <= hex_length(hex))
		check = 0;
	if (tmp == 0)
		check--;
	if (flags->plus > 0 && tmp >= 0)
		writechar('+', flags);
	while (check > 0)
	{
		writechar(fill, flags);
		check--;
	}
	flags->ll ? ll_nbr_final(hex, flags, tmp) : nbr_final(hex, flags, tmp);
}

void	hex_onlywidth(t_struct *flags, unsigned int hex,
		unsigned int tmp)
{
	int		check;

	check = flags->width - hex_getcountp(flags, hex, tmp);
	if (tmp <= 0)
		check--;
	if (flags->zero > 0)
		writeprefix(hex, flags);
	if (flags->minus > 0)
	{
		if (flags->zero == 0)
			writeprefix(hex, flags);
		flags->ll ? ll_nbr_final(hex, flags, tmp) : nbr_final(hex, flags, tmp);
	}
	while (check > 0)
	{
		flags->zero ? writechar('0', flags) : writechar(' ', flags);
		check--;
	}
	if (flags->minus == 0)
	{
		if (flags->zero == 0)
			writeprefix(hex, flags);
		flags->ll ? ll_nbr_final(hex, flags, tmp) : nbr_final(hex, flags, tmp);
	}
}

void	hex_widthandprecision(t_struct *flags, unsigned int hex,
		unsigned int tmp)
{
	int		check_w;
	int		count_p;
	char	fill;

	fill = ' ';
	count_p = hex_getcountp(flags, hex, tmp);
	check_w = flags->width - count_p;
	if (flags->width < count_p)
		check_w = 0;
	if (flags->minus > 0)
		hex_onlyprecision(flags, hex, tmp);
	while (check_w > 0)
	{
		writechar(fill, flags);
		check_w--;
	}
	if (flags->minus == 0)
		hex_onlyprecision(flags, hex, tmp);
}

void	printhex(va_list ap, t_struct *flags)
{
	unsigned int			hex;
	unsigned int			tmp;

	hex = va_arg(ap, unsigned int);
	tmp = hex;
	if ((flags->precision > 0 || flags->width > 0) && hex < 0)
		hex = hex * -1;
	if (flags->width > 0 && flags->precision == 0)
		hex_onlywidth(flags, hex, tmp);
	if (flags->precision != 0 && flags->width == 0)
		hex_onlyprecision(flags, hex, tmp);
	if (flags->width > 0 && flags->precision != 0)
		hex_widthandprecision(flags, hex, tmp);
	if (flags->width == 0 && flags->precision == 0)
	{
		writeprefix(hex, flags);
		nbr_final(hex, flags, tmp);
	}
}
