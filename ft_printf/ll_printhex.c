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

void	ll_nbr_final(unsigned long long hex, t_struct *flags,
		unsigned long long tmp)
{
	if (flags->plus > 0 && flags->width == 0
	&& flags->precision == 0 && tmp >= 0)
		writechar('+', flags);
	if (hex >= 16)
	{
		ll_nbr_final((hex / 16), flags, tmp);
		ll_nbr_final((hex % 16), flags, tmp);
	}
	if (hex < 16)
	{
		if (flags->capital > 0)
			converthex_capitalx(hex, flags);
		else
			converthex_x(hex, flags);
	}
}

void	ll_printhex(va_list ap, t_struct *flags)
{
	unsigned long long			hex;
	unsigned long long			tmp;

	hex = va_arg(ap, unsigned long long);
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
		ll_nbr_final(hex, flags, tmp);
	}
}
