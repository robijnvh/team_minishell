/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printunsigned_int.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 11:53:44 by rvan-hou      #+#    #+#                 */
/*   Updated: 2019/12/12 11:53:45 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			ll_putnbru_int(unsigned long long n, t_struct *flags)
{
	char	y;

	if (n < 0)
	{
		writechar('-', flags);
		n = n * -1;
	}
	if (n >= 10)
	{
		ll_putnbru_int((n / 10), flags);
		ll_putnbru_int((n % 10), flags);
	}
	else
	{
		y = 48 + n;
		writechar(y, flags);
	}
}

void			ll_printu_int(va_list ap, t_struct *flags)
{
	unsigned long long		digit;
	unsigned long long		tmp;

	digit = va_arg(ap, unsigned long long);
	tmp = digit;
	if ((flags->precision > 0 || flags->width > 0) && digit < 0)
		digit = digit * -1;
	if (flags->width > 0 && flags->precision == 0)
		u_onlywidth(flags, digit, tmp);
	if (flags->precision != 0 && flags->width == 0)
		u_onlyprecision(flags, digit, tmp);
	if (flags->width > 0 && flags->precision != 0)
		u_widthandprecision(flags, digit, tmp);
	if (flags->width == 0 && flags->precision == 0)
		u_ft_putstringdigits(digit, flags, tmp);
}
