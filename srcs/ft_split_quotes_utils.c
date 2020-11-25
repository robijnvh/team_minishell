/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_quotes_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:46:59 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/24 16:31:49 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		fill_char_s(char *str, char **new, int *i, int *n)
{
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
	while (str[*i] != '\'')
	{
		(*new)[*n] = str[*i];
		(*n)++;
		(*i)++;
	}
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
}

void		fill_char_d(char *str, char **new, int *i, int *n)
{
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
	while (!(str[*i] == '\"' && !check_slash(str, i)) && str[*i] != 0)
	{
		(*new)[*n] = str[*i];
		(*n)++;
		(*i)++;
	}
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
}
