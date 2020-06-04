/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 14:21:55 by Marty         #+#    #+#                 */
/*   Updated: 2020/06/04 15:34:32 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_data *e)
{
	int i;

	i = 0;
	while (i < 255)
	{
		e->par_cnt = 0;
		e->arr_cnt = 0;
		e->cmd[i] = NULL;
		(e->params)[i] = NULL;
		e->wtf[i] = 0;
		e->wtf_i[i] = -1;
		e->append[i] = -1;
		e->trunc[i] = -1;
		e->param_count[i] = 0;
		e->new_file[i] = NULL;
		i++;
	}
}

int		split_params(t_data *e, char ***array, char **cmds)
{
	int i;
	int j;

	i = 0;
	while (array[i])
	{
		j = 0;
		e->cmd[i] = ft_strdup(array[i][j]);
		e->param_count[i] = print_array(e, array[i], 0, 0) - 1;
		if (e->param_count[i] == 0)
		{
			(e->params)[i] = NULL;
			i++;
			continue ;
		}
		e->params[i] = malloc(sizeof(char *) * e->param_count[i] + 1);
		while (array[i][j + 1])
		{
			(e->params)[i][j] = ft_strdup(array[i][j + 1]);
			j++;
		}
		(e->params)[i][j] = NULL;
		i++;
	}
	while (i >= 0)
	{
		free_array(array[i], 0);
		i--;
	}
	*cmds ? free_array(cmds, 0) : 0;
	return (0);
}

int		split_cmds(char *line, t_data *e)
{
	char	**array[255];
	char	**cmds;
	int		i;
	int		j;

	cmds = ft_split_actions(line, ';');
	if (!cmds)
		return (0);
	i = print_array(e, cmds, 0, 0) - 1;
	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (ft_strnstr(cmds[i], ">", strlen(cmds[i])))
			e->wtf[i] = 1;
		array[j] = ft_split_params(cmds[i]);
		// array[j] = ft_parser(cmds[i], e);
		print_array(e, array[j], 0, 0);
		i++;
		j++;
	}
	array[j] = NULL;
	split_params(e, array, cmds);
	return (0);
}

int		read_input(t_data *e)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_line(&line, e);
	if (!ret)
		return (0);
	split_cmds(line, e);
	free(line);
	return (1);
}

int		options(t_data *e)
{
	e->i = 0;
	while (e->cmd[e->i])
	{
		e->j = 0;
		if (!ft_strcmp(e->cmd[e->i], "$?")) // moet in echo
		{
			free(e->cmd[e->i]);
			e->cmd[e->i] = ft_itoa(e->ret);
		}
		if (!ft_strcmp(e->cmd[e->i], ">") || !ft_strcmp(e->cmd[e->i], ">>"))
			open_file(e);
		if (e->wtf[e->i])
			init_wtf(e);
		// if (!ft_strcmp(e->cmd[e->i], "ls"))
		// 	list_dir(e);
		else if (!ft_strcmp(e->cmd[e->i], "exit"))
			exit(0);
		else if (!ft_strcmp(e->cmd[e->i], "env"))
			display_env(e);
		else if (!ft_strcmp(e->cmd[e->i], "echo"))
			run_echo(e);
		else if (!ft_strcmp(e->cmd[e->i], "export"))
			add_env(e);
		else if (!ft_strcmp(e->cmd[e->i], "unset"))
			cut_env(e);
		else if (!ft_strcmp(e->cmd[e->i], "cd"))
			change_dir(e);
		// else if (!ft_strcmp(e->cmd[e->i], "rmdir"))
		// 	remove_dir(e);
		// else if (!ft_strcmp(e->cmd[e->i], "mkdir"))
		// 	make_dir(e);
		else if (!ft_strcmp(e->cmd[e->i], "pwd"))
			get_path(e);
		else if (!ft_strcmp(e->cmd[e->i], "clear"))
			e->first = 0;
		else if (((e->cmd[e->i][0] == '.' && e->cmd[e->i][1] == '/') || e->cmd[e->i][0] == '/') && e->wtf[e->i])
			exec_to_file(e);
		else if ((e->cmd[e->i][0] == '.' && e->cmd[e->i][1] == '/') || e->cmd[e->i][0] == '/')
			executable(e);
		else
			if (!e->wtf[e->i])
				printf("bash: %s: command not found\n", e->cmd[e->i]);
		e->i++;
	}
	e->i = 0;
	while (e->cmd[e->i])
		free(e->cmd[e->i++]);
	e->i = 0;
	while (e->params[e->i] != NULL)
	{
		free_array(e->params[e->i], 0);
		e->i++;
	}
	return (0);
}

int		main(int argc, char **argv, char *envp[])
{
	t_data	e;

	e.first = 0;
	e.ret = 0;
	/**
	 * In principe moet dit aan staan zodat je in de root directory begint maar met testen is het handiger om gewoon in de minishell map te zitten.
	 * 
	 * e.path = "/";
	 * chdir(e.path);
	 */
	init_cd(&e);
	init_env(envp, &e);
	while (1)
	{
		init_struct(&e);
		signal(SIGINT, block_ctrl_c);
		prompt(&e);
		if (read_input(&e))
		{
			if (options(&e))
				return (0);
		}
		else
			return (0);
	}
	return (0);
	(void)argc;
	(void)argv;
}
