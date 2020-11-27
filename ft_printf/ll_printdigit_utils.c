/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_printdigit_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 14:25:55 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/27 11:28:39 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			ll_ft_putstringdigits(long long digit, t_struct *flags,
				long long tmp)
{
	if (flags->plus > 0 && flags->width == 0
	&& flags->precision == 0 && tmp >= 0)
		writechar('+', flags);
	ll_ft_putnbrdigit(digit, flags);
}

long long		ll_getcountp(t_struct *flags, long long digit, long long tmp)
{
	long long		ret;

	ret = flags->precision;
	if (flags->precision == -1)
		return (0);
	if (flags->precision <= ll_intlength(digit))
		ret = ll_intlength(digit);
	if (tmp < 0)
		ret++;
	if (flags->plus > 0 && tmp >= 0)
		ret++;
	return (ret);
}

long long		ll_intlength(long long n)
{
	long long		i;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void			ll_ft_putnbrdigit(long long n, t_struct *flags)
{
	char	y;

	if (n < 0)
	{
		writechar('-', flags);
		n = n * -1;
	}
	if (n >= 10)
	{
		ll_ft_putnbrdigit((n / 10), flags);
		ll_ft_putnbrdigit((n % 10), flags);
	}
	else
	{
		y = 48 + n;
		writechar(y, flags);
	}
}
