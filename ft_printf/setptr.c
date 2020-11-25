/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setptr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/15 13:39:22 by robijnvanho    #+#    #+#                */
/*   Updated: 2019/12/15 13:54:20 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	setptr(va_list ap, t_struct *flags)
{
	int	*ptr;

	ptr = va_arg(ap, int*);
	ptr[0] = flags->count;
}
