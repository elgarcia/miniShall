/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:57 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/28 01:30:34 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	**list_to_array(t_env_lst *env)
{
	t_env_lst	*tmp;
	char		**array;
	int			i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (0);
	i = 0;
	tmp = env;
	while (tmp)
	{
		array[i] = ft_strjoin(tmp->name, "=");
		array[i] = ft_strjoinfree(array[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	array[i] = 0;
	return (array);
}

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

int	ft_strlenchr(const char *s, char c)
{
	int	i;

	if (!s)
		return (-2);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
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
