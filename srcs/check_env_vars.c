/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_env_vars.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 15:22:27 by Marty         #+#    #+#                 */
/*   Updated: 2020/11/30 15:25:33 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_var_str(char *ptr)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	if (!ptr)
		return (NULL);
	while (ft_isalpha(ptr[len]) || ft_isdigit(ptr[len]))
		len++;
	str = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*replace(t_data *e, char *to_add, char *var, int i)
{
	char	*new_str;
	char	*tmp;

	if (!to_add)
		return (NULL);
	new_str =
	ft_substr(e->params[i], 0, ft_strchr(e->params[i], '$') - e->params[i]);
	tmp = new_str;
	new_str = ft_strjoin3(new_str, to_add,
	ft_strchr2(e->params[i], '$') + ft_strlen(var));
	free(tmp);
	return (new_str);
}

void	check(t_data *e, char **ptr, int i)
{
	int		i2;
	char	*var;
	char	*tmp;

	while (1)
	{
		var = make_var_str(ft_strchr2(*ptr, '$'));
		if (!var)
			break ;
		i2 = 0;
		while (e->env[i2])
		{
			if (ft_strnstr(e->env[i2], var, ft_strlen(var)))
			{
				tmp = e->params[i];
				e->params[i] = replace(e, ft_strchr2(e->env[i2], '='), var, i);
				free(tmp);
			}
			i2++;
		}
		tmp = *ptr;
		*ptr = ft_strdup(ft_strchr2(*ptr, '$'));
		free(tmp);
		free(var);
	}
}

void	check_for_env_vars(t_data *e)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (e->params[i])
	{
		ptr = ft_strdup(ft_strchr(e->params[i], '$'));
		if (ptr)
			check(e, &ptr, i);
		i++;
	}
	ptr ? free(ptr) : 0;
}
