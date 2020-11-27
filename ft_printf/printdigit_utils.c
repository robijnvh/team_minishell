/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printdigit_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 14:25:55 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/27 11:28:43 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			ft_putstringdigits(int digit, t_struct *flags, int tmp)
{
	if (flags->plus > 0 && flags->width == 0
	&& flags->precision == 0 && tmp >= 0)
		writechar('+', flags);
	ft_putnbrdigit(digit, flags);
}

int				getcountp(t_struct *flags, int digit, int tmp)
{
	int		ret;

	ret = flags->precision;
	if (tmp == 0 && flags->precision == -1)
	{
		if (flags->plus > 0)
			return (1);
		return (0);
	}
	if (flags->precision == -1)
	{
		if (flags->plus > 0)
			return (ilen(digit) + 1);
		return (0);
	}
	if (flags->precision <= ilen(digit))
		ret = ilen(digit);
	if (tmp < 0)
		ret++;
	if (flags->plus > 0 && tmp >= 0)
		ret++;
	return (ret);
}
