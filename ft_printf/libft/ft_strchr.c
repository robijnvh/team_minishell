/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 08:31:38 by rvan-hou      #+#    #+#                 */
/*   Updated: 2020/11/30 11:04:37 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	char *ptr;

	if (!str)
		return (0);
	ptr = (char *)str;
	while (*ptr != c)
	{
		if (!*ptr)
			return (0);
		ptr++;
	}
	return (ptr);
}
