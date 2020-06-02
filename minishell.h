/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 15:43:59 by Marty         #+#    #+#                 */
/*   Updated: 2020/06/02 10:56:35 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/syslimits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h> //
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>

typedef struct	minishell
{
	char		*line;
	char		**env;
	int			param_count[255];
	char		**params[255];
	int			append[255];
	int			trunc[255];
	int			wtf_i[255];
	char		*cmd[255];
	int			wtf[255];
	char		*new_file[255];
	char		buf[PATH_MAX];
	int			first;
	char		*path;
	int			i;
	int			j;
	int			ret;
	int			fd[255];
	int			is_child;
	int			check_quote;
}				t_data;

/* utils */
int					get_next_line(int fd, char **line);
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s1);
size_t				ft_strcpy(char *dst, const char *src);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *s);
size_t				cnt_prnt_array(char **array, int print, char div);
int					print(char **array);
int					get_line(char **line);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char				*ft_itoa(int n);
void				ft_putnbr_fd(int n, int fd);
/* exec */
void				exec_to_file(t_data *e); //26 lines
void				executable(t_data *e);
/* cd */
void				change_dir(t_data *e);
void				list_dir(t_data *e);
void				get_path(t_data *e);
/* dir */
void				make_dir(t_data *e);
void				remove_dir(t_data *e);
/* write to file */
int					wtf(t_data *e, char *s, int i);
int					init_wtf(t_data *e);
int					open_file(t_data *e);
/* minishell utils */
int					index_off(char **array, char *str);
size_t				print_array(t_data *e, char **array, int print, char div);
void				prompt(t_data *e);
void				free_array(char **array, int size);
/* ctrl */
void				block_ctrl_c(int sig);
/* env */
int					display_env(t_data *e);
int					add_env(t_data *e); //50 lines + 30
int					cut_env(t_data *e); //27 lines
void				init_env(char **envp, t_data *e);
int					check_char(char c);
void				free_test(char **str);
int					count_parameters(t_data *e);
int					check_string(char *str);
int					ft_strcmp_env(const char *s1, const char *s2, size_t n);
int					check_input_cut(t_data *e);
char				**ft_sort(char **order, int n);
void				exp_no_params(t_data *e);
int					check_input_add(t_data *e);
/* echo */
void				run_echo(t_data *e);
/* utils 2 */
void				*ft_memalloc(size_t size);
void				ft_bzero(void *s, size_t n);
void				ft_putstr_exp(char *s);
void				ft_putstr(char *s);
void    			ft_putchar(char c);
/* split params */
char				**ft_split_params(char *str);
#endif
