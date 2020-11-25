/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printunsigned_int_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 14:25:55 by rvan-hou      #+#    #+#                 */
/*   Updated: 2019/12/11 14:25:56 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			u_ft_putstringdigits(unsigned long int digit, t_struct *flags,
				unsigned long int tmp)
{
	if (flags->plus > 0 && flags->width == 0
	&& flags->precision == 0 && tmp >= 0)
		writechar('+', flags);
	flags->ll ? ll_putnbru_int(digit, flags) : ft_putnbru_int(digit, flags);
}

int				u_getcountp(t_struct *flags, unsigned long int digit,
				unsigned long int tmp)
{
	int		ret;

	ret = flags->precision;
	if (flags->precision == -1)
		return (0);
	if (flags->precision <= u_intlength(digit))
		ret = u_intlength(digit);
	if (tmp < 0)
		ret++;
	if (flags->plus > 0 && tmp >= 0)
		ret++;
	return (ret);
}

void			ft_putnbru_int(long long n, t_struct *flags)
{
	char	y;

	if (n < 0)
	{
		writechar('-', flags);
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbru_int((n / 10), flags);
		ft_putnbru_int((n % 10), flags);
	}
	else
	{
		y = 48 + n;
		writechar(y, flags);
	}
}

int				u_intlength(long long n)
{
	int		i;

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
