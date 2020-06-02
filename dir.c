/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dir.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:18:23 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/02 10:19:06 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_dir(t_data *e)
{
	int ret;

	ret = mkdir(e->params[e->i][e->j], S_IRUSR |
	S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
}

void	remove_dir(t_data *e)
{
	int ret;

	ret = rmdir(e->params[e->i][e->j]);
}
