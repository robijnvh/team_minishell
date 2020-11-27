/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setptr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 18:17:27 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/27 11:31:10 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	setptr(va_list ap, t_struct *flags)
{
	int	*ptr;

	ptr = va_arg(ap, int*);
	ptr[0] = flags->count;
}
