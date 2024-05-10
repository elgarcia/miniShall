/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/10 16:56:32 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_shell *shell, char *str, t_env_lst *env)
{
	t_env_lst	*tmp;
	char		*exit_status;

	tmp = env;
	if (str[0] == '?')
	{
		exit_status = ft_itoa(shell->exit_status);
		if (!exit_status)
			exit_error("Malloc failed");
		return (exit_status);
	}
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
	int		i;

	i = 0;
	new = malloc(ft_strlen(s1) + 2);
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

char	*extend_expansor(t_shell *shell, char *new, char *tmp)
{
	char	*env_value;
    char	*rst;

	env_value = get_env(shell, tmp, shell->paths->env_lst);
	if (!env_value)
		exit_error("Malloc failed");
	new = ft_strjoinfree(new, env_value);
	if (!new)
		exit_error("Malloc failed");
	free(tmp);
	free(env_value);
	tmp = NULL;
	rst = ft_add_quotes(new);
	return (rst);
}

void	get_variable(t_shell *shell, char **new, char *str, int *i)
{
	char	*tmp;
	int		j;

	j = *i + 1;
	while ((str[j] && ft_isalnum(str[j])) || str[j] == '_' || str[j] == '?')
		j++;
	tmp = ft_substr(str, *i + 1, j - *i - 1);
    if (!tmp)
        exit_error("Malloc failed");
	*new = extend_expansor(shell, *new, tmp);
	*i = j - 1;
}

char	*expansor(t_shell *shell, char *str, int i)
{
	char	*new;
	int		quotes;
	int		double_quotes;

	new = ft_strdup("");
    if (!new)
        exit_error("Malloc failed");
	quotes = 0;
	double_quotes = 0;
    i = 0;
	while (str[i])
	{
        quotes = (quotes + (!double_quotes && str[i] == '\'')) % 2;
		double_quotes = (double_quotes + (!quotes && str[i] == '\"')) % 2;
		if (!quotes && str[i] == '$' && str[i + 1] && str[i
				+ 1] != ' ' && str[i + 1] != '$')
			get_variable(shell, &new, str, &i);
		else
			new = ft_strjoin_char(new, str[i]);
        i++;
	}
	return (new);
}
