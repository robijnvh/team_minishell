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

void	u_onlyprecision(t_struct *flags, unsigned long int digit,
		unsigned long int tmp)
{
	int		check;
	char	fill;

	fill = '0';
	check = flags->precision - u_intlength(digit);
	if (flags->precision == -1)
	{
		if (tmp != 0)
			u_ft_putstringdigits(digit, flags, tmp);
		return ;
	}
	if (flags->precision <= u_intlength(digit))
		check = 0;
	if (tmp < 0)
		writechar('-', flags);
	if (flags->plus > 0 && tmp >= 0)
		writechar('+', flags);
	while (check > 0)
	{
		writechar(fill, flags);
		check--;
	}
	u_ft_putstringdigits(digit, flags, tmp);
}

void	u_checkbeforecases(t_struct *flags, unsigned long int digit,
		unsigned long int tmp, char *fill)
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
		u_ft_putstringdigits(digit, flags, tmp);
	}
	if (flags->plus > 0 && tmp >= 0 && *fill == '0')
		writechar('+', flags);
}

void	u_onlywidth(t_struct *flags, unsigned long int digit,
		unsigned long int tmp)
{
	int		check;
	char	fill;

	fill = ' ';
	check = flags->width - u_intlength(digit);
	if (tmp < 0 || flags->plus > 0)
		check--;
	u_checkbeforecases(flags, digit, tmp, &fill);
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
		u_ft_putstringdigits(digit, flags, tmp);
}

void	u_widthandprecision(t_struct *flags, unsigned long int digit,
		unsigned long int tmp)
{
	int		check_w;
	int		count_p;
	char	fill;

	fill = ' ';
	count_p = u_getcountp(flags, digit, tmp);
	check_w = flags->width - count_p;
	if (flags->width < count_p)
		check_w = 0;
	if (flags->minus > 0)
		u_onlyprecision(flags, digit, tmp);
	while (check_w > 0)
	{
		writechar(fill, flags);
		check_w--;
	}
	if (flags->minus == 0)
		u_onlyprecision(flags, digit, tmp);
}

void	printu_int(va_list ap, t_struct *flags)
{
	unsigned long int		digit;
	unsigned long int		tmp;

	digit = va_arg(ap, unsigned int);
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
