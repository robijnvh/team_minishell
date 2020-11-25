/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 13:41:17 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/23 12:51:23 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putstr_env(char *str, int s, int d)
{
	int o;
	int i;

	if (!str)
		return ;
	o = outer_quote(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && d % 2 == 0 &&
		count_quote(str, str[i]) % 2 == 0 && o != '\'')
			i++;
		else if (str[i] == '\'' && s % 2 == 0 &&
		count_quote(str, str[i]) % 2 == 0 && o != '\"')
			i++;
		else if (str[i] == '\\' && str[i + 1] &&
		str[i + 1] == '\\' && o != '\'')
			i++;
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}

void	*ft_memalloc(size_t size)
{
	unsigned char *mem;

	mem = (unsigned char*)malloc(sizeof(size_t) * size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
