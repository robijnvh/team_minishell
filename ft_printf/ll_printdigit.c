/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_printdigit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 11:35:18 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/27 11:35:22 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ll_onlyprecision(t_struct *flags, long long digit, long long tmp)
{
	int		check;
	char	fill;

	fill = '0';
	check = flags->precision - ll_intlength(digit);
	if (flags->precision == -1)
	{
		if (tmp != 0)
			ll_ft_putstringdigits(digit, flags, tmp);
		return ;
	}
	if (flags->precision <= ll_intlength(digit))
		check = 0;
	if (flags->space > 0 && tmp >= 0 && flags->plus == 0 && flags->width == 0)
		writechar(' ', flags);
	if (tmp < 0)
		writechar('-', flags);
	if (flags->plus > 0 && tmp >= 0)
		writechar('+', flags);
	while (check > 0)
	{
		writechar(fill, flags);
		check--;
	}
	ll_ft_putstringdigits(digit, flags, tmp);
}

void	ll_checkbeforecases(t_struct *flags, long long digit,
long long tmp, char *fill)
{
	if (flags->zero > 0 && flags->minus == 0)
	{
		*fill = '0';
		if (tmp < 0)
			writechar('-', flags);
	}
	if (flags->minus > 0)
	{
		if (tmp < 0)
			writechar('-', flags);
		ll_ft_putstringdigits(digit, flags, tmp);
	}
	if (flags->plus > 0 && tmp >= 0 && *fill == '0')
		writechar('+', flags);
}

void	ll_onlywidth(t_struct *flags, long long digit, long long tmp)
{
	int		check;
	char	fill;

	fill = ' ';
	check = flags->width - ll_intlength(digit);
	if (tmp < 0 || flags->plus > 0)
		check--;
	if (flags->space > 0 && tmp >= 0 && flags->plus == 0)
	{
		writechar(' ', flags);
		check--;
	}
	ll_checkbeforecases(flags, digit, tmp, &fill);
	while (check > 0)
	{
		writechar(fill, flags);
		check--;
	}
	if (flags->plus > 0 && tmp >= 0 && fill == ' ')
		writechar('+', flags);
	if (flags->zero == 0 && tmp < 0 && flags->minus == 0)
		writechar('-', flags);
	if (flags->minus == 0)
		ll_ft_putstringdigits(digit, flags, tmp);
}

void	ll_widthandprecision(t_struct *flags, long long digit, long long tmp)
{
	int		check_w;
	int		count_p;
	char	fill;

	fill = ' ';
	count_p = ll_getcountp(flags, digit, tmp);
	check_w = flags->width - count_p;
	if (flags->width < count_p)
		check_w = 0;
	if (flags->space > 0 && tmp >= 0 && flags->plus == 0
	&& flags->width <= flags->precision)
		writechar(' ', flags);
	if (flags->minus > 0)
		ll_onlyprecision(flags, digit, tmp);
	while (check_w > 0)
	{
		writechar(fill, flags);
		check_w--;
	}
	if (flags->minus == 0)
		ll_onlyprecision(flags, digit, tmp);
}

void	ll_printdigit(va_list ap, t_struct *flags)
{
	long long		digit;
	long long		tmp;

	digit = va_arg(ap, long long);
	tmp = digit;
	if ((flags->precision > 0 || flags->width > 0) && digit < 0)
		digit = digit * -1;
	if (flags->width > 0 && flags->precision == 0)
		ll_onlywidth(flags, digit, tmp);
	if (flags->precision != 0 && flags->width == 0)
		ll_onlyprecision(flags, digit, tmp);
	if (flags->width > 0 && flags->precision != 0)
		ll_widthandprecision(flags, digit, tmp);
	if (flags->width == 0 && flags->precision == 0)
	{
		if (flags->space > 0 && tmp >= 0 && flags->plus == 0)
			writechar(' ', flags);
		ll_ft_putstringdigits(digit, flags, tmp);
	}
}
