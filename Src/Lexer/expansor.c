/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/02 12:07:05 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (ft_strdup(""));
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*new;

	new = malloc(ft_strlen(s1) + 2);
	new = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
	if (!new)
	{
		perror("Error al asignar memoria para el nuevo string");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	new[ft_strlen(s1)] = c;
	free(s1);
	s1 = NULL;
	return (new);
}

char	*extend_expansor(t_shell *shell, char *new, char *tmp)
{
	char	*env_value;

	env_value = get_env(tmp, shell->paths->env_lst);
	new = ft_strjoin(new, env_value);
	free(tmp);
	free(env_value);
	tmp = NULL;
	return (new);
}

char	*expansor(t_shell *shell, char *str, int i, int j)
{
	char	*new;
	int		quotes;
	char	*tmp;

	new = ft_strdup("");
	quotes = 1;
	while (str[++i])
	{
		if (str[i] == '\'')
			quotes = !quotes;
		if (quotes && str[i] == '$' && str[i + 1] && str[i + 1] != ' ' && \
				str[i + 1] != '$')
		{
			j = i + 1;
			while ((str[j] && ft_isalnum(str[j])) || \
			str[j] == '_' || str[j] == '?')
				j++;
			tmp = ft_substr(str, i + 1, j - i - 1);
			new = extend_expansor(shell, new, tmp);
			i = j - 1;
		}
		else
			new = ft_strjoin_char(new, str[i]);
	}
	return (new);
}
