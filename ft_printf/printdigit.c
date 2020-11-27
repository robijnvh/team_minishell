/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:38:47 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/27 11:27:15 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	onlyprecision(t_struct *flags, int digit, int tmp)
{
	int		c;
	char	fill;

	fill = '0';
	c = flags->precision <= ilen(digit) ? 0 : flags->precision - ilen(digit);
	if (flags->precision == -1)
	{
		if (flags->plus > 0)
			writechar('+', flags);
		if (tmp != 0)
			ft_putstringdigits(digit, flags, tmp);
		return ;
	}
	if (flags->space > 0 && tmp >= 0 && flags->plus == 0 && flags->width == 0)
		writechar(' ', flags);
	if (tmp < 0)
		writechar('-', flags);
	if (flags->plus > 0 && tmp >= 0)
		writechar('+', flags);
	while (c > 0)
	{
		writechar(fill, flags);
		c--;
	}
	ft_putstringdigits(digit, flags, tmp);
}

void	checkbeforecases(t_struct *flags, int digit, int tmp, char *fill)
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
		ft_putstringdigits(digit, flags, tmp);
	}
	if (flags->plus > 0 && tmp >= 0 && *fill == '0')
		writechar('+', flags);
}

void	onlywidth(t_struct *flags, int digit, int tmp)
{
	int		check;
	char	fill;

	fill = ' ';
	check = flags->width - ilen(digit);
	if (tmp < 0 || flags->plus > 0)
		check--;
	if (flags->space > 0 && tmp >= 0 && flags->plus == 0)
	{
		writechar(' ', flags);
		check--;
	}
	checkbeforecases(flags, digit, tmp, &fill);
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
		ft_putstringdigits(digit, flags, tmp);
}

void	widthandprecision(t_struct *flags, int digit, int tmp)
{
	int		check_w;
	int		count_p;
	char	fill;

	fill = ' ';
	count_p = getcountp(flags, digit, tmp);
	check_w = flags->width - count_p;
	if (flags->width < count_p)
		check_w = 0;
	if (flags->space > 0 && tmp >= 0 && flags->plus == 0)
	{
		writechar(' ', flags);
		check_w--;
	}
	if (flags->minus > 0)
		onlyprecision(flags, digit, tmp);
	while (check_w > 0)
	{
		writechar(fill, flags);
		check_w--;
	}
	if (flags->minus == 0)
		onlyprecision(flags, digit, tmp);
}

void	printdigit(va_list ap, t_struct *flags)
{
	int		digit;
	int		tmp;

	digit = va_arg(ap, int);
	tmp = digit;
	if ((flags->precision > 0 || flags->width > 0) && digit < 0)
		digit = digit * -1;
	if (flags->width > 0 && flags->precision == 0)
		onlywidth(flags, digit, tmp);
	if (flags->precision != 0 && flags->width == 0)
		onlyprecision(flags, digit, tmp);
	if (flags->width > 0 && flags->precision != 0)
		widthandprecision(flags, digit, tmp);
	if (flags->width == 0 && flags->precision == 0)
	{
		if (flags->space > 0 && tmp >= 0 && flags->plus == 0)
			writechar(' ', flags);
		ft_putstringdigits(digit, flags, tmp);
	}
}
