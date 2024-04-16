/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:27:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/16 15:17:41 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*join_paths(const char *path1, const char *path2)
{
	char	*result;
	char	*tmp;

	if (!path1 || !path2)
		return (NULL);
	tmp = ft_strjoin(path1, "/");
	result = ft_strjoin(tmp, path2);
	if (!result)
		return (NULL);
	free(tmp);
	return (result);
}

char	*get_previous_dir(char *str)
{
	int		i;
	char	*new;
	char	*aux;

	if (!str)
		return (NULL);
	aux = ft_strrchr(str, '/');
	i = (aux - str);
	new = ft_substr(str, 0, i);
	if (!new[0])
	{
		free(new);
		new = ft_strdup("/");
	}
	return (new);
}

char	*get_full_path(char *current_dir, char *target)
{
	return (join_paths(current_dir, target));
}
