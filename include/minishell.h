/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 15:43:59 by Marty         #+#    #+#                 */
/*   Updated: 2020/12/01 11:44:14 by robijnvanho   ########   odam.nl         */
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
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"
# include "printf.h"
# include <errno.h>

extern int			g_ctrl_c;

typedef struct		s_data
{
	char			*line;
	char			**env;
	char			**params;
	char			**cmds;
	char			*new_file;
	char			buf[PATH_MAX];
	int				first;
	char			*path;
	char			*og_path;
	int				ret;
	char			**bins;
	int				pipe_count;
	int				**pipe;
	char			**pipe_split;
	int				fd_write;
	int				fd_read;
	int				re_in;
	int				re_out;
	int				arr_cnt;
	int				par_cnt;
	int				quit;
	int				quit2;
	int				write;
	int				pids;
	int				is_child;
}					t_data;

int					ft_strlen2(char *str);
char				*ft_strchr2(char *str, int c);
void				ft_putstr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					get_line(char **line);
void				*ft_memalloc(size_t size);
void				ft_putstr_exp(char *s);
int					ft_isquote(char c);
int					ft_isspace(int c);
void				ft_putstr_no_quotes(char *s);
int					count_chars(char *str, char a, char b);
int					count_quote(char *s, char c);
void				free_and_zero(char **str);
char				*ft_strjoin3(char *s1, char *s2, char *s3);
int					change_dir(t_data *e, int check);
void				set_path(t_data *e, char *str);
int					wrong_cd_arg(t_data *e, int i, int *check);
int					check_cd_arg(t_data *e, int i);
char				*trim(char *str, int c);
int					only_cd(t_data *e, int num);
int					check_spaces_in_path(t_data *e, int i, int check);
void				prompt(t_data *e);
int					index_off(char **array, char *str);
void				*free_array(char ***array);
char				**ft_split_actions(char *s, char c);
char				**ft_split_quotes(char *str);
void				fill_char_s(char *str, char **new, int *i, int *n);
void				fill_char_d(char *str, char **new, int *i, int *n);
void				init_struct(t_data *e);
void				error_message(t_data *e, int error);
void				free_and_stuff(t_data *e, int error, int ex);
void				display_ret(t_data *e);
void				sig_handler(int sig);
int					display_env(t_data *e);
void				init_env(char **envp, t_data *e);
int					add_env(t_data *e);
int					cut_env(t_data *e);
int					check_char(char c, int i, int j, t_data *e);
int					check_string(char *str);
int					ft_strcmp_env(char *str1, char *str2, int n);
int					check_input_cut(t_data *e, int j);
int					exp_no_params(t_data *e);
int					ft_strcmp_exp(char *s1, char *s2);
char				*fill_str(char *str, int env, t_data *e);
void				ft_putstr_env(char *str, int s, int d);
int					outer_quote(char *s);
int					check_for_env(t_data *e, int j);
void				export_env_var(t_data *e, int j);
size_t				print_array(char **array, int print, char div);
int					run_echo(t_data *e);
int					check_slash(char *str, int *index);
void				find_char(char *str, int *i, char d);
char				**ft_trim_args(char **args);
void				write_echo(char *str, int param, t_data *e, int i);
void				write_backslash(t_data *e, char *str, int *i, int param);
int					is_alpha_num(char c);
int					is_alpha_no_num(char c);
void				create_two_spaces(char **str);
int					ft_isquote(char c);
void				init_execute(t_data *e);
int					find_bin_paths(t_data *e);
void				*trim_args(t_data *e);
void				open_pipes(t_data *e);
void				set_pipe(t_data *e, int n);
void				close_pipes(t_data *e, int n);
void				redirect(t_data *e);
void				return_values(t_data *e);
int					improve_line(t_data *e);
void				run_exit(t_data *e);
int					ft_strcmp_cmd(const char *s1, const char *s2);
void				del_quotes(t_data *e);
int					ft_isquote(char c);
void				check_for_env_vars(t_data *e);

#endif
