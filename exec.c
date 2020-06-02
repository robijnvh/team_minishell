/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 10:13:11 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/02 10:15:38 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executable(t_data *e)
{
	int status;

	status = 0;
	if (fork())
		waitpid(-1, &status, 0);
	else
		execve(e->cmd[e->i], e->params[e->i], 0);
	e->ret = WEXITSTATUS(status);
}

void	exec_to_file(t_data *e)
{
	int fd;
	int ret;
	int status;

	status = 0;
	if (fork())
		waitpid(-1, &status, 0);
	else
	{
		if (e->append[e->i])
		{
			fd = open(e->new_file[e->i], O_APPEND | O_WRONLY);
			if (fd == -1)
				printf("Open error\n");
		}
		else if (e->trunc[e->i])
		{
			fd = open(e->new_file[e->i], O_CREAT | O_WRONLY | O_TRUNC);
			if (fd == -1)
				printf("Open error\n");
		}
		ret = dup2(fd, 1);
		execve(e->cmd[e->i], e->params[e->i], 0);
		close(fd);
	}
	e->ret = WEXITSTATUS(status);
}

// void	exec_to_file(t_data *e)
// {
// 	int fd;
// 	int ret;

// 	fd = open(e->params[e->i][e->wtf_i[e->i] + 1], O_CREAT | O_RDWR | O_APPEND);
// 	ret = dup2(fd, 1);
// 	execve(e->cmd[e->i], e->params[e->i], 0);
// 	close(fd);
// }
