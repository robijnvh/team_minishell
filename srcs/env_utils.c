/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 15:23:43 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/11/30 12:19:30 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_str(char *str, int env, t_data *e)
{
	int		i;
	char	*tmp;

	i = 0;
	if (env == 1 && check_for_env(e, env) != -1)
	{
		str = e->env[check_for_env(e, env)];
		while (str[i] != '=' && str[i] != '\0')
			i++;
		if (str[i] != '=' && str[i] != '\0')
			return (NULL);
		i++;
	}
	tmp = (char *)ft_memalloc(PATH_MAX + 1);
	tmp ? 0 : free_and_stuff(e, 0, 1);
	while (str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

int		check_char(char c, int i, int j, t_data *e)
{
	if (i == 0 && ((c >= '0' && c <= '9') || (c == '=')))
	{
		ft_printf(2, "bash: export: `%s': not a valid identifier\n",
		e->params[j]);
		return (0);
	}
	if (!((c >= 'A' && c <= 'Z') || (c == '_') || (c >= 'a' && c <= 'z')
	|| (c >= '0' && c <= '9')))
		return (0);
	return (1);
}

int		count_parameters(t_data *e)
{
	int index;

	index = 0;
	while (e->params[index] != NULL)
		index++;
	return (index);
}

int		check_string(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		ft_strcmp_exp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
