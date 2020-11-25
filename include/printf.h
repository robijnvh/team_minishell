/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 18:17:27 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/07 21:46:57 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct			s_struct
{
	int					i;
	int					count;
	int					minus;
	int					plus;
	int					space;
	int					zero;
	char				*type;
	int					hash;
	int					width;
	int					precision;
	int					ll;
	int					capital;
}						t_struct;
int						ft_printf(int fd, const char *format, ...);
int						openlist(const char *format, va_list ap);
void					checkflags(const char *format, va_list ap,
						t_struct *flags, int index);
void					checktype(const char *format, t_struct *flags,
						va_list ap);
int						ft_atoi(const char *str);
void					flagszero(t_struct *flags, int index);
char					*ft_strchr(const char *str, int c);
int						getwidth(const char *format, t_struct *flags,
						va_list ap);
int						getprecision(const char *format, t_struct *flags,
						va_list ap);
void					printchar(t_struct *flags, va_list ap);
void					writechar(char c, t_struct *flags);
void					ft_putchar(char c);
size_t					ft_strlen(const char *str);
void					printstring(t_struct *flags, va_list ap);
void					ft_putstring(char *s, t_struct *flags);
void					checkwidth(t_struct *flags, char *str);
void					printdigit(va_list ap, t_struct *flags);
void					ft_putstringdigits(int digit, t_struct *flags, int tmp);
void					widthandprecision(t_struct *flags, int digit, int tmp);
void					checkbeforecases(t_struct *flags, int digit,
						int tmp, char *fill);
void					onlywidth(t_struct *flags, int digit, int tmp);
void					onlyprecision(t_struct *flags, int digit, int tmp);
int						getcountp(t_struct *flags, int digit, int tmp);
void					ft_putnbrdigit(long n, t_struct *flags);
int						ilen(int n);
void					printu_int(va_list ap, t_struct *flags);
void					u_widthandprecision(t_struct *flags,
						unsigned long int digit, unsigned long int tmp);
void					u_checkbeforecases(t_struct *flags,
						unsigned long int digit, unsigned long int tmp,
						char *fill);
void					u_onlyprecision(t_struct *flags,
						unsigned long int digit, unsigned long int tmp);
void					u_onlywidth(t_struct *flags, unsigned long int digit,
						unsigned long int tmp);
void					ft_putnbru_int(long long n, t_struct *flags);
int						u_intlength(long long n);
int						u_getcountp(t_struct *flags, unsigned long int digit,
						unsigned long int tmp);
void					u_ft_putstringdigits(unsigned long int digit,
						t_struct *flags, unsigned long int tmp);
void					printpercent(t_struct *flags);
void					printptr(va_list ap, t_struct *flags);
void					ptr_width(t_struct *flags, unsigned long ptr);
void					ptr_writeprefix(t_struct *flags);
int						ptr_length(unsigned long hex);
void					ptr_nbr_final(unsigned long hex, t_struct *flags,
						unsigned long tmp);
void					ptr_precision(t_struct *flags, unsigned long ptr);
void					printhex(va_list ap, t_struct *flags);
void					hex_widthandprecision(t_struct *flags,
						unsigned int hex, unsigned int tmp);
void					hex_onlywidth(t_struct *flags, unsigned int hex,
						unsigned int tmp);
void					hex_onlyprecision(t_struct *flags, unsigned int hex,
						unsigned int tmp);
void					nbr_final(unsigned int hex, t_struct *flags,
						unsigned int tmp);
int						hex_getcountp(t_struct *flags, unsigned int hex,
						unsigned inttmp);
int						hex_length(unsigned int hex);
void					converthex_capitalx(unsigned int res, t_struct *flags);
void					converthex_x(unsigned int res, t_struct *flags);
void					writeprefix(unsigned int hex, t_struct *flags);
void					setptr(va_list ap, t_struct *flags);
void					ll_printdigit(va_list ap, t_struct *flags);
void					ll_ft_putstringdigits(long long digit, t_struct *flags,
						long long tmp);
void					ll_checkbeforecases(t_struct *flags, long long digit,
						long long tmp, char *fill);
void					ll_onlyprecision(t_struct *flags,
						long long digit, long long tmp);
void					ll_onlywidth(t_struct *flags, long long digit,
						long long tmp);
void					ll_widthandprecision(t_struct *flags, long long digit,
						long long tmp);
long long				ll_getcountp(t_struct *flags, long long digit,
						long long tmp);
long long				ll_intlength(long long n);
void					ll_ft_putnbrdigit(long long n, t_struct *flags);
void					ll_printu_int(va_list ap, t_struct *flags);
void					ll_putnbru_int(unsigned long long n, t_struct *flags);
void					ll_printhex(va_list ap, t_struct *flags);
void					ll_nbr_final(unsigned long long hex, t_struct *flags,
						unsigned long long tmp);

#endif
