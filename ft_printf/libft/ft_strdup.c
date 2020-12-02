/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 14:12:13 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/12/02 10:46:40 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	int			i;
	char		*copy;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
		i++;
	copy = (char *)malloc(sizeof(*src) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
