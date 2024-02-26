/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:57 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 17:26:32 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	*ft_strchrt(char *s, char c, int times)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			i++;
			if (i == times)
				return (s);
		}
		s++;
	}
	return (0);
}

char	*get_prompt()
{
	char	*prompt;
	char	*tmp;

	tmp = ft_strchrt((char*)getcwd(NULL, 0), '/', 3);
	if (!tmp)
		tmp = "/";
	prompt = ft_strjoin("~", tmp);
	return (prompt);
}
