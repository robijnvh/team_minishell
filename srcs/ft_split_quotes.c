/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 13:51:23 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/24 16:31:55 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_count_words(char *s, int words, int i)
{
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i])
		words++;
	while (s[i] && s[i] != 10)
	{
		if (s[i] == '\'' && !check_slash(s, &i))
			find_char(s, &i, '\'');
		else if (s[i] == '\"' && !check_slash(s, &i))
			find_char(s, &i, '\"');
		else if (!(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)) && s[i] != 0)
			i++;
		else if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		{
			while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
				i++;
			if (s[i])
				words++;
		}
	}
	return (words);
}

void		fill_word(char **new, char *str, int i)
{
	int i2;

	i2 = 0;
	while (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
	{
		if (str[i] == '\'' && !check_slash(str, &i))
			fill_char_s(str, new, &i, &i2);
		else if (str[i] == '\"' && !check_slash(str, &i))
			fill_char_d(str, new, &i, &i2);
		else
		{
			(*new)[i2] = str[i];
			i++;
			i2++;
		}
	}
	(*new)[i2] = 0;
}

char		*ft_find_word(char *str, int *i, char s, char d)
{
	int		index;
	char	*word;

	index = *i;
	while (!(str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)) && str[*i])
	{
		if (str[*i] == s && !check_slash(str, i))
			find_char(str, i, s);
		else if (str[*i] == d && !check_slash(str, i))
			find_char(str, i, d);
		else
			(*i)++;
	}
	word = malloc(*i - index + 1);
	if (word == NULL)
		return (NULL);
	fill_word(&word, str, index);
	return (word);
}

char		**ft_split_quotes(char *str)
{
	int		i;
	int		k;
	char	**array;

	k = 0;
	i = 0;
	array = malloc(sizeof(char *) * (ft_count_words(str, 0, 0) + 1));
	if (!array)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			break ;
		array[k] = ft_find_word(str, &i, '\'', '\"');
		k++;
	}
	array[k] = 0;
	return (array);
}
