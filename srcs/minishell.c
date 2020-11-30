/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 14:21:55 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/29 10:11:07 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_ctrl_c = 0;

void	zero_struct(t_data *e)
{
	e->first = 0;
	e->ret = 0;
	e->is_child = 0;
	e->new_file = NULL;
	e->params = NULL;
	e->pipe_split = NULL;
	e->pipe = NULL;
	e->path = NULL;
	e->bins = NULL;
	e->re_in = -1;
	e->re_out = -1;
	e->pipe_count = 0;
	e->fd_read = -1;
	e->fd_write = -1;
	e->pids = 0;
	errno = 0;
	if (!getcwd(e->buf, PATH_MAX))
		free_and_stuff(e, 1, 0);
	e->og_path = ft_strdup(e->buf);
	e->og_path ? 0 : free_and_stuff(e, 0, 1);
}

void	options(t_data *e)
{
	if (index_off(e->params, "$?") >= 0)
		display_ret(e);
	e->ret = 0;
	if (!ft_strcmp_cmd(e->params[0], "exit"))
		run_exit(e);
	else if (!ft_strcmp_cmd(e->params[0], "env"))
		display_env(e);
	else if (!ft_strcmp_cmd(e->params[0], "echo"))
		run_echo(e);
	else if (!ft_strcmp_cmd(e->params[0], "export"))
		add_env(e);
	else if (!ft_strcmp_cmd(e->params[0], "unset"))
		cut_env(e);
	else if (!ft_strcmp_cmd(e->params[0], "cd"))
		change_dir(e, 0);
	else if (!ft_strcmp_cmd(e->params[0], "pwd"))
		ft_printf(1, "%s\n", e->buf);
	else if (!ft_strcmp_cmd(e->params[0], "clear"))
		e->first = 0;
	else
		init_execute(e);
}

void	do_it(t_data *e, int n)
{
	e->params = ft_split_quotes(e->pipe_split[n]);
	if (!e->params)
		free_and_stuff(e, 1, 1);
	set_pipe(e, n);
	redirect(e);
	e->params = trim_args(e);
	if (e->params)
		options(e);
	close_pipes(e, n);
	e->params ? free_array(&e->params) : 0;
	if (e->pipe_split && e->pipe_split[n + 1])
		do_it(e, n + 1);
}

void	loop(t_data *e)
{
	int		i;

	if (improve_line(e))
	{
		free_and_zero(&e->line);
		return ;
	}
	e->cmds = ft_split_actions(e->line, ';');
	free_and_zero(&e->line);
	errno ? free_and_stuff(e, 1, 0) : 0;
	i = 0;
	while (e->cmds[i])
	{
		init_struct(e);
		e->pipe_split = ft_split(e->cmds[i], '|');
		!e->pipe_split ? free_and_stuff(e, 1, 1) : 0;
		open_pipes(e);
		do_it(e, 0);
		free_and_stuff(e, 0, 0);
		i++;
	}
	free_array(&e->cmds);
}

int		main(int argc, char **argv, char *envp[])
{
	t_data	e;

	zero_struct(&e);
	init_env(envp, &e);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		prompt(&e);
		if (!get_line(&e.line))
			free_and_stuff(&e, 8, 2);
		e.ret += g_ctrl_c;
		g_ctrl_c = 0;
		loop(&e);
	}
	return (0);
	(void)argc;
	(void)argv;
}
