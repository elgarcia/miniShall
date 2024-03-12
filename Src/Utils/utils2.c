/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:25:57 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/12 22:45:04 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	**list_to_array(t_env_lst *env)
{
	t_env_lst	*tmp;
	char		**array;
	int			i;

	tmp = env;
	i = -1;
	while (tmp && ++i >= 0)
		tmp = tmp->next;
	array = (char **)malloc(sizeof(char *) * (i + 2));
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
	if (!s)
		return (0);
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

void	check_status(t_shell *all, int status)
{
	if (WIFEXITED(status) && !is_builting(all->lst_process))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3");
		printf("\n");
		g_exit_status = 128 + WTERMSIG(status);
	}
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	*tmp2;
	char	*path;

	path = malloc(PATH_MAX);
	if (!path)
		exit(EXIT_FAILURE);
	tmp = ft_strchrt((char *)getcwd(path, PATH_MAX), '/', 3);
	if (!tmp)
		tmp = (BLUE_TEXT "/" RESET_TEXT);
	tmp2 = ft_strjoin((BLUE_TEXT "~"), tmp);
	prompt = ft_strjoinfree(tmp2,
			(RESET_TEXT GREEN_TEXT " minishall > " RESET_TEXT));
	free(path);
	return (prompt);
}
