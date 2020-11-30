/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ctrl.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:33:50 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/29 09:45:49 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_ctrl_c = 1;
		ft_putstr_fd("\nminishell> ", 1);
	}
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}
