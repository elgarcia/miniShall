/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/21 17:22:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

char	*get_env(char *str, t_env_lst *env)
{
	t_env_lst	*tmp;

	tmp = env;
	if (str[0] == '?')
		return (ft_itoa(g_exit_status));
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return ("");
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(s1) + 2);
	if (!new)
	{
		perror("Error al asignar memoria para el nuevo string");
		exit(EXIT_FAILURE);
	}
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(s1);
	s1 = NULL;
	return (new);
}

char	*expansor(t_shell *shell, char *str, int i, int j)
{
	char	*new;
	char	*tmp;
	char	*env_value;

	new = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while ((str[j] && ft_isalnum(str[j])) || str[j] == '_' || str[j] == '?')
				j++;
			tmp = ft_substr(str, i + 1, j - i - 1);
			env_value = get_env(tmp, shell->paths->env_lst);
			new = ft_strjoin(new, env_value);
			free(tmp);
			tmp = NULL;
			i = j - 1;
		}
		else
			new = ft_strjoin_char(new, str[i]);
		i++;
	}
	return (new);
}
