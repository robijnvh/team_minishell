/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 14:21:55 by Marty         #+#    #+#                 */
/*   Updated: 2020/05/06 14:50:09 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_data *e)
{
	e->multi = 0;
	e->pipe = 0;
	e->exec = 0;
	e->echo = 0;
	e->env = 0;
	e->sp = 0;
	e->mp = 0;
	int i = 0;
	while (i < 255)
	{
		e->cmd[i++] = NULL;
		(e->params)[i] = NULL;
		e->wtf[i] = 0;
	}
}

int		index_off(char **array, char *str)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], str))
			return (i);
		i++;
	}
	return (-1);
}

/**
 * >>/> write to file
 */
int		wtf(t_data *e, char *s, int i)
{
	int fd;
	int j;

	j = index_off(e->params[e->i], ">");
	if (j == -1)
		j = index_off(e->params[e->i], ">>");
	if (i == j || i == j + 1)
		return (0);
	fd = open(e->params[e->i][j + 1], O_RDWR | O_APPEND, 0777);
	if (fd < 0 || !ft_strcmp(e->params[e->i][j], ">"))
		fd = open(e->params[e->i][j + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	return (0);
}

size_t		print_array(t_data *e, char **array, int print, char div)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		if (print)
		{
			if (e->wtf[e->i])
				wtf(e, array[i], i);
			else
			{
				write(1, array[i], ft_strlen(array[i]));
				if (array[i + 1])
					write(1, &div, 1);
			}
		}
		i++;
	}
	if (!e->wtf[e->i])
		write(1, "\n", 1);
	return (i);
}

/**
 * Clear screen & prompt
 */
void	prompt(t_data *e)
{
	if (!e->first)
		e->first = write(1, " \e[1;1H\e[2J", 12);
	write(1, "$> ", 3);
}

void	free_array(char **array, int size)
{
	int i;

	i = 0;
	if (!array)
		return ;
	if (size)
		while (size >= 0)
		{
			size--;
			free(array[size]);
		}
	else
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	array ? free(array) : 0;
}

int		split_cmds_from_params(char *line, t_data *e)
{
	char **array[255];
	char **cmds;
	int i;
	int j = 0;

	/**
	 * Split commands by ;
	 */
	cmds = ft_split(line, ';');
	i = print_array(e, cmds, 0, 0) - 1;
	i = 0;
	while (cmds[i])
	{
		if (ft_strnstr(cmds[i], ">", strlen(cmds[i])))
			e->wtf[i] = 1;
		array[j] = ft_split(cmds[i], ' ');
		print_array(e, array[j], 0, 0);
		i++;
		j++;
	}
	array[j] = NULL;

	/**
	 *	Make cmd and param arrays
	 */
	i = 0;
	while (array[i])
	{
		j = 0;
		e->cmd[i] = ft_strdup(array[i][j]);
		if (print_array(e, array[i], 0, 0) == 1)
		{
			(e->params)[i] = NULL;
			i++;
			continue ;
		}
		e->params[i] = malloc(sizeof(char *) * print_array(e, array[i], 0, 0));
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
	free_array(cmds, 0);
	return (0);
}

int		read_input(t_data *e)
{
	char	**array;
	char	*line;
	int		i;

	i = 0;
	array = NULL;
	line = NULL;

	/**
	 * Read input
	 */
	get_line(&line);
	if (!line)
		return (0);
	
	split_cmds_from_params(line, e);
	free(line);
	return (1);
}

/**
 * pwd
 */
void	get_path()
{
	char buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
}

/**
 * mkdir
 */
void	make_dir(t_data *e)
{
	int ret;

	ret = mkdir(e->params[e->i][e->j], S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
}

/**
 * rmdir
 */
void	remove_dir(t_data *e)
{
	int ret;

	ret = rmdir(e->params[e->i][e->j]);
}

/**
 * echo
 */
int		echo(t_data *e)
{
	print_array(e, e->params[e->i], 1, ' ');
	return (0);
}

/**
 * cd ..
 */
char	*trim(char *str, int c)
{
	int i;
	int ret;
	int count;

	i = 0;
	ret = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			ret = i;
			count++;
		}
		i++;
	}
	if (count == 1)
		return (ft_strdup("/"));
	return (ft_substr(str, 0, ret));
}

/**
 * cd
 */
void	change_dir(t_data *e)
{
	int ret;
	
	getcwd(e->buf, PATH_MAX);
	if (!ft_strcmp(e->params[e->i][e->j], ".."))
		e->path = trim(e->buf, '/');
	else if (e->params[e->i][e->j][0] != '/')
	{
		e->path = ft_strjoin("/", e->params[e->i][e->j]);
		e->path = ft_strjoin(e->buf, e->path);
	}
	else
		e->path = ft_strjoin(e->buf, e->params[e->i][e->j]);
	chdir(e->path);
	free(e->path);
}


/**
 * ls
 */
void	list_dir(t_data *e)
{
	DIR *dir;
	struct dirent *sd;

	dir = opendir(".");
	sd = malloc(sizeof(sd));
	while (sd)
	{
		sd = readdir(dir);
		if (sd)
		{
			if (e->wtf[e->i])
				wtf(e, sd->d_name, -1);
			else
				printf("- %s\n", sd->d_name);
		}
	}
	closedir(dir);
	free(sd);
}

/**
 * >>/> create and write to file from stdin
 */
int		open_file(t_data *e)
{
	int fd;
	int j;
	char *input;
	int ret;

	fd = open(e->params[e->i][0], O_RDWR | O_APPEND, 0777);
	if (fd < 0 || !ft_strcmp(e->cmd[e->i], ">"))
		fd = open(e->params[e->i][0], O_RDWR | O_CREAT | O_TRUNC, 0777);
	j = 1;
	while (1)
	{
		ret = get_line(&input);
		if (ret < 0)
		{
			free(input);
			return (0);
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	return (0);
}

int		options(t_data *e)
{
	e->i = 0;
	while (e->cmd[e->i])
	{
		e->j = 0;
		if (!ft_strcmp(e->cmd[e->i], ">>") || !ft_strcmp(e->cmd[e->i], ">"))
			open_file(e);
		if (!ft_strcmp(e->cmd[e->i], "ls"))
			list_dir(e);
		if (!ft_strcmp(e->cmd[e->i], "exit"))
			return (1);
		if (!ft_strcmp(e->cmd[e->i], "cd"))
			change_dir(e);
		if (!ft_strcmp(e->cmd[e->i], "rmdir"))
			remove_dir(e);
		if (!ft_strcmp(e->cmd[e->i], "mkdir"))
			make_dir(e);
		if (!ft_strcmp(e->cmd[e->i], "pwd"))
			get_path();
		if (!ft_strcmp(e->cmd[e->i], "clear"))
			e->first = 0;
		if (!ft_strcmp(e->cmd[e->i], "echo"))
			echo(e);
		if (e->cmd[e->i][0] == '.' && e->cmd[e->i][1] == '/')
		{
			if (fork())
				wait(NULL);
			else
				execve(e->cmd[e->i], e->params[e->i], 0);
		}
		e->i++;
	}
	e->i = 0;
	while (e->cmd[e->i])
		free(e->cmd[e->i++]);
	return (0);
}

int		main(void)
{
	t_data	e;
	
	e.first = 0;
	/**
	 * In principe moet dit aan staan zodat je in de root directory begint maar met testen is het handiger om gewoon in de minishell map te zitten.
	 * 
	 * e.path = "/";
	 * chdir(e.path);
	 */
	while (1)
	{
		init_struct(&e);
		prompt(&e);
		if (read_input(&e))
		{
			if (options(&e))
				return (0);
		}
	}
	return (0);
}
