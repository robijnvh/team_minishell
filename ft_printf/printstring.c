/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printstring.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 11:24:51 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/07 21:42:02 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		ft_putstring2(char *s, t_struct *flags)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	if ((flags->precision > 0 || flags->precision == -1)
	&& flags->precision < (int)ft_strlen(s))
	{
		while (flags->precision > 0)
		{
			ft_putchar_fd(s[i], flags->fd);
			i++;
			flags->count++;
			flags->precision--;
		}
	}
	else
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], flags->fd);
			i++;
			flags->count++;
		}
	}
}

void		checkwidth(t_struct *flags, char *str)
{
	int		check;
	char	fill;

	check = flags->width - flags->precision;
	if (flags->precision > flags->width)
		check = 0;
	if (flags->precision >= (int)ft_strlen(str))
		check = flags->width - (int)ft_strlen(str);
	if (flags->precision == -1)
		check = flags->width;
	if (flags->precision == 0)
		check = flags->width - (int)ft_strlen(str);
	fill = ' ';
	if (flags->minus > 0)
		ft_putstring2(str, flags);
	while (check > 0)
	{
		if (flags->zero > 0 && flags->minus == 0)
			fill = '0';
		ft_putchar_fd(fill, flags->fd);
		flags->count++;
		check--;
	}
	if (flags->minus == 0)
		ft_putstring2(str, flags);
}

void		printstring(t_struct *flags, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	if (flags->width > 0)
		checkwidth(flags, str);
	else
		ft_putstring2(str, flags);
}
