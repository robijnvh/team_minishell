/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 15:31:45 by robijnvanho   #+#    #+#                 */
/*   Updated: 2020/05/27 15:14:09 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
	// return (c == ' ' || c == '\t');
}

int			ft_isquote(char c)
{
	return (c == '\"' || c == '\'');
}

int		count_words(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && ft_isquote(*str))
		{
			count++;
			str++;
			while (*str && !ft_isquote(*str)) // inbouwen dat er een spatie na moet komen
				str++;
			str++;
		}
		else if (*str && !ft_isspace(*str))
		{
			count++;
			while (*str && !ft_isspace(*str))
				str++;
		}
	}
	return (count);
}

char	*malloc_string(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i + 1] && !ft_isquote(str[i + 1]))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i + 1] && !ft_isquote(str[i + 1]))
	{
		word[i] = str[i + 1];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*malloc_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	if (ft_isquote(str[i]))
	{
		word = malloc_string(str);
		return (word);
	}
	while (str[i] && !ft_isspace(str[i]))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

// klopt nog niet volledig qua aantal params
char	**ft_split_params(char *str)
{
	int		i;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
	i = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && ft_isquote(*str))
		{
			arr[i] = malloc_word(str);
			i++;
			str++;
			while (*str && !ft_isquote(*str))
				str++;
			str++;
		}
		else if (*str && !ft_isspace(*str))
		{
			arr[i] = malloc_word(str);
			i++;
			while (*str && !ft_isspace(*str))
				str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

// int		main(void)
// {
// 	char	*test;
// 	char	**ret;

// 	test = "Hoi doei \"hoe gaat het\" yo";
// 	ret = ft_split_params(test);
// 	while (*ret != NULL)
// 	{
// 		printf("%s\n", *ret);
// 		ret++;
// 	}
// }
