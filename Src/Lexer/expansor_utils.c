/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:16:42 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 17:14:03 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free_null(&s1);
	return (new);
}

int	is_builting_exp(char *argv)
{
	if (!ft_strcmp(argv, "echo"))
		return (1);
	if (!ft_strcmp(argv, "cd"))
		return (1);
	if (!ft_strcmp(argv, "pwd"))
		return (1);
	if (!ft_strcmp(argv, "env"))
		return (1);
	if (!ft_strcmp(argv, "export"))
		return (1);
	if (!ft_strcmp(argv, "unset"))
		return (1);
	return (0);
}

void	remove_quotes(char *arg)
{
	if (arg[0] == '\"' || (arg[0] == '\'' && arg[1] != '$'))
		remove_char(arg, arg[0]);
}
