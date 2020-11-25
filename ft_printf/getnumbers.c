/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getnumbers.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 11:26:03 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/13 11:59:57 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static long int	ft_amax(const char *str, unsigned long int res, int sign, int i)
{
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if ((res > 922337203685477580 || res == 922337203685477580)
		&& ((str[i] - '0') > 7) && sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || res == 922337203685477580)
		&& ((str[i] - '0') > 8) && sign == -1)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int				pf_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == ' ' ||
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (str[i] == '+' && sign != -1)
		i++;
	res = ft_amax(str, res, sign, i);
	return ((int)res * sign);
}

int				getwidth(const char *format, t_struct *flags, va_list ap)
{
	int	ret;

	if (format[flags->i] == '*')
	{
		ret = va_arg(ap, int);
		if (ret < 0)
		{
			ret = ret * -1;
			flags->minus = 1;
		}
	}
	else
	{
		ret = pf_atoi(&format[flags->i]);
		while (format[flags->i] >= '0' && format[flags->i] <= '9')
			flags->i++;
		flags->i--;
	}
	return (ret);
}

int				getprecision(const char *format, t_struct *flags, va_list ap)
{
	int	ret;

	if (format[flags->i] == '.' && format[flags->i + 1] == '*')
	{
		ret = va_arg(ap, int);
		if (ret < 0)
			return (0);
		flags->i++;
	}
	else if (format[flags->i + 1] >= '0' && format[flags->i + 1] <= '9')
	{
		flags->i++;
		ret = pf_atoi(&format[flags->i]);
		while (format[flags->i] >= '0' && format[flags->i] <= '9')
			flags->i++;
		flags->i--;
	}
	else
		ret = 0;
	if (ret == 0)
		ret = -1;
	return (ret);
}
