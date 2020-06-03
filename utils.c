/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 12:55:14 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/06/03 15:47:18 by rvan-hou      ########   odam.nl         */
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

void	ft_putstr_exp(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		ft_putchar(s[i]);
		i++;
	}
	if (s[i] == '=')
		ft_putchar(s[i]);
	else
		return ;
	ft_putchar('\"');
	i++;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	ft_putchar('\"');
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
