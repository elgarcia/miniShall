/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:27:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/23 23:48:05 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

char	*join_paths(const char *path1, const char *path2)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(path1, "/");
	result = ft_strjoin(tmp, path2);
	free(tmp);
	return (result);
}

char	*get_previous_dir(char *str)
{
	int		i;
	char	*new;
	char	*aux;

	aux = ft_strrchr(str, '/');
	i = (aux - str);
	new = ft_substr(str, 0, i);
	if (!new[0])
		new = ft_strdup("/");
	return (new);
}

char	*get_full_path(char *current_dir, char *target)
{
	return (join_paths(current_dir, target));
}
