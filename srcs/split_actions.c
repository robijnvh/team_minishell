/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 13:06:49 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/24 16:38:45 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			find_char(char *str, int *i, char d)
{
	(*i)++;
	if (d == '\"')
	{
		while (!(str[*i] == d && !check_slash(str, i)) && str[*i] != 0)
			(*i)++;
		(*i)++;
		return ;
	}
	while (str[*i] && str[*i] != d)
		(*i)++;
	(*i)++;
}

static int		ft_countwords(char *s, char c, int count)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (1);
	while (s[i] && s[i] != 10)
	{
		while (s[i] == c)
			i++;
		if (s[i] != 10 && s[i] != c && s[i] != 10)
		{
			count++;
			while ((s[i]) && (s[i] != c) && s[i] != 10)
			{
				if (s[i] == '\'' && !check_slash(s, &i))
					find_char(s, &i, '\'');
				else if (s[i] == '\"' && !check_slash(s, &i))
					find_char(s, &i, '\"');
				else
					i++;
			}
		}
	}
	return (count);
}

static int		ft_wordlength(char *s, char c)
{
	int	i;

	i = 0;
	while ((s[i]) && (s[i] != c) && s[i] != 10)
	{
		if (s[i] == '\'' && !check_slash(s, &i))
			find_char(s, &i, '\'');
		else if (s[i] == '\"' && !check_slash(s, &i))
			find_char(s, &i, '\"');
		else
			i++;
	}
	return (i);
}

static char		*ft_mallocword(char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c && s[i] != 10)
	{
		if (s[i] == '\'' && !check_slash(s, &i))
			find_char(s, &i, '\'');
		else if (s[i] == '\"' && !check_slash(s, &i))
			find_char(s, &i, '\"');
		else
			i++;
	}
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	word[i] = '\0';
	while (i > 0)
	{
		i--;
		word[i] = s[i];
	}
	return (word);
}

char			**ft_split_actions(char *s, char c)
{
	int		i;
	int		n;
	char	**arr;

	i = 0;
	n = 0;
	arr = malloc(sizeof(char *) * (ft_countwords(s, c, 0) + 1));
	if (arr == NULL)
		return (NULL);
	while (s[i] && s[i] != 10)
	{
		if (s[i] != c)
		{
			arr[n] = ft_mallocword(s + i, c);
			if (arr[n] == NULL)
				return (free_array(&arr));
			i = i + ft_wordlength(s + i, c);
			n++;
		}
		while (s[i] == c)
			i++;
	}
	arr[n] = 0;
	return (arr);
}
