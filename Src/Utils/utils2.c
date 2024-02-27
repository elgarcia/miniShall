/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:57 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/27 22:29:05 by bautrodr         ###   ########.fr       */
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

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strchrt((char *)getcwd(NULL, 0), '/', 3);
	if (!tmp)
		tmp = (BLUE_TEXT "/" RESET_TEXT);
	tmp2 = ft_strjoin((BLUE_TEXT "~"), tmp);
	prompt = ft_strjoin(tmp2,
			(RESET_TEXT GREEN_TEXT " minishall > " RESET_TEXT));
	free(tmp2);
	return (prompt);
}
