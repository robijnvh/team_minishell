/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 15:09:51 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/03 15:33:51 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			ft_putnbrdigit(long n, t_struct *flags)
{
	char	y;

	if (n < 0)
	{
		writechar('-', flags);
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbrdigit((n / 10), flags);
		ft_putnbrdigit((n % 10), flags);
	}
	else
	{
		y = 48 + n;
		writechar(y, flags);
	}
}

int				ilen(int n)
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

int				ptr_length(unsigned long hex)
{
	int		ret;

	ret = 0;
	while (hex)
	{
		hex = hex / 16;
		ret++;
	}
	return (ret);
}
