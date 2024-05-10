/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:40:13 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 19:25:46 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*free_all(char **str)
{
	free(*str);
	(*str) = NULL;
	return (NULL);
}

char	*ft_get_line(char *str)
{
	char	*s;
	char	*aux;
	int		i;

	aux = ft_strchr_gnl(str, '\n');
	if (!aux)
		aux = ft_strchr_gnl(str, '\0');
	i = (aux - str) + 1;
	s = ft_substr_gnl(str, 0, i);
	if (!s)
		return (NULL);
	return (s);
}

char	*update_str(char *str)
{
	char	*new_str;
	char	*aux;
	size_t	len;

	aux = ft_strchr_gnl(str, '\n');
	if (!aux)
		return (free_all(&str));
	len = (aux - str) + 1;
	if (str[len] == '\0')
		return (free_all(&str));
	new_str = ft_substr_gnl(str, len, ft_strlen_gnl(str) - len);
	free(str);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*read_line(int fd, char *str)
{
	int		rd;
	char	*temp;

	rd = BUFFER_SIZE;
	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free_all(&str));
	temp[0] = '\0';
	while (rd == BUFFER_SIZE && !ft_strchr_gnl(temp, '\n'))
	{
		rd = read(fd, temp, BUFFER_SIZE);
		if (rd > 0)
		{
			temp[rd] = '\0';
			str = ft_strjoin2_gnl(str, temp);
			if (!str)
				return (free_all(&temp));
		}
	}
	free(temp);
	if (rd == -1)
		return (free_all(&str));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((str && !ft_strchr_gnl(str, '\n')) || !str)
		str = read_line(fd, str);
	if (!str)
		return (NULL);
	s = ft_get_line(str);
	if (!s)
		return (free_all(&str));
	str = update_str(str);
	return (s);
}
