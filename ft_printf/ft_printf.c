/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 12:13:11 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/07 21:29:12 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	flagszero(t_struct *flags, int index)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->hash = 0;
	flags->width = 0;
	flags->type = NULL;
	flags->precision = 0;
	flags->capital = 0;
	flags->ll = 0;
	flags->i = index;
}

void	checktype(const char *format, t_struct *flags, va_list ap)
{
	if (format[flags->i] == 'c')
		printchar(flags, ap);
	if (format[flags->i] == 's')
		printstring(flags, ap);
	if (format[flags->i] == 'd' || format[flags->i] == 'i')
		flags->ll ? ll_printdigit(ap, flags) : printdigit(ap, flags);
	if (format[flags->i] == 'u')
		flags->ll ? ll_printu_int(ap, flags) : printu_int(ap, flags);
	if (format[flags->i] == 'p')
		printptr(ap, flags);
	if (format[flags->i] == 'x' || format[flags->i] == 'X')
	{
		if (format[flags->i] == 'X')
			flags->capital = 1;
		flags->ll ? ll_printhex(ap, flags) : printhex(ap, flags);
	}
	if (format[flags->i] == '%')
		printpercent(flags);
	if (format[flags->i] == 'n')
		setptr(ap, flags);
	if (format[flags->i] == '\0')
		flags->count = 0;
}

void	checkflags(const char *format, va_list ap, t_struct *flags, int index)
{
	flagszero(flags, index);
	while (ft_strchr("cspdiuxX%n", format[flags->i]) == 0 &&
	format[flags->i] != '\0')
	{
		if (format[flags->i] == '-')
			flags->minus = 1;
		if (format[flags->i] == '0')
			flags->zero = 1;
		if (format[flags->i] == '+')
			flags->plus = 1;
		if (format[flags->i] == ' ')
			flags->space = 1;
		if (format[flags->i] == '#')
			flags->hash = 1;
		if (((format[flags->i] >= '0' && format[flags->i] <= '9') ||
		(format[flags->i] == '*')) && format[flags->i - 1] != '.')
			flags->width = getwidth(format, flags, ap);
		if (format[flags->i] == '.')
			flags->precision = getprecision(format, flags, ap);
		if (format[flags->i] == 'l' && format[flags->i + 1] == 'l')
			flags->ll = 1;
		flags->i++;
	}
	flags->type = ft_strchr("cspdiuxX%n", format[flags->i]);
	checktype(format, flags, ap);
}

int		openlist(int fd, const char *format, va_list ap)
{
	t_struct	*flags;
	int			index;

	flags = malloc(sizeof(t_struct));
	flags->count = 0;
	index = 0;
	flags->fd = fd;
	while (format[index] != '\0')
	{
		if (format[index] != '%')
			writechar(format[index], flags);
		if (format[index] == '%')
		{
			index++;
			checkflags(format, ap, flags, index);
			while (ft_strchr("cspdiuxX%n", format[index]) == 0)
				index++;
		}
		if (format[index] != 0)
			index++;
	}
	free(flags);
	return (flags->count);
}

int		ft_printf(int fd, const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = openlist(fd, format, ap);
	va_end(ap);
	return (ret);
}
