/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:00:57 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/06/04 14:29:29 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		ft_isspace(char c)
// {
// 	return ((c == '\t' || c == '\v' || c == '\n' ||
// c == '\r' || c == '\f' || c == ' '));
// }

int		ft_isseparator(char c)
{
	return ((c == ';' || c == '|' || c == '<' || c == '>'));
}

int		get_size_2(char **str, int *size)
{
	if (*(*str) == '\\' && (*size)++ && ((*str) += (*((*str) + 1)) ? 2 : 1))
		return (1);
	else if (*(*str) == '\'' && (*str)++)
	{
		while (*(*str) && *(*str) != '\'' && !ft_isseparator(*(*str)) && ++(*size))
			(*str)++;
		(*str) += (*(*str) == '\'') ? 1 : 0;
		return (1);
	}
	else if (*(*str) == '\"' && (*str)++)
	{
		while (*(*str) && *(*str) != '\"' && !ft_isseparator(*(*str)))
		{
			if (*(*str) == '\\' && ++(*size))
				(*str) += (*((*str) + 1)) ? 2 : 1;
			// else if (check_envv_and_size(&(*str), &(*size)) < 0)
				// return (-1);
		}
		(*str) += (*(*str) == '\"') ? 1 : 0;
		return (1);
	}
	return (0);
}

int			get_size(char *str)
{
	int		ret;
	int		size;

	size = 0;
	while (*str && !ft_isseparator(*str))
	{
		ret = get_size_2(&str, &size);
		if (ret < 0)
			return (-1);
		else if (!ret)
		{
			if (*str && ((!ft_isspace(*str) && !ft_isseparator(*str)) || (*(str + 1) &&
			(!ft_isspace(*(str + 1)) && !ft_isseparator(*(str + 1))))))
			{
				// if (check_envv_and_size(&str, &size) < 0)
					return (-1);
			}
			else
				str++;
		}
	}
	return (size);
}

char		**ft_parser(char const *str, t_data *e)
{
	int	size;
	int	i;
	char	**array;

	if (!str)
		return (NULL);
	printf("check: %d\n", get_size((char*)str));
	// array = (char**)malloc(sizeof(char*) * (get_size((char*)str) + 1));
	// if (!array)
		// return (NULL);
	return (array);
}

// int		main(void)
// {
// 	char	*str;
	
// 	str = (char*)malloc(sizeof(char) * (PATH_MAX + 1));
// 	str = " \" "\\"    "\""   \\   \'   \"";
// }