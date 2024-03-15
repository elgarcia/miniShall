/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/06 16:09:07 by bautrodr         ###   ########.fr       */
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
	int		i;

	i = 0;
	new = malloc(ft_strlen(s1) + 2);
	if (!new)
	{
		perror("Malloc Failed");
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

char	*extend_expansor(t_shell *shell, char *new, char *tmp)
{
	char	*env_value;

	env_value = get_env(tmp, shell->paths->env_lst);
	new = ft_strjoinfree(new, env_value);
	free(tmp);
	free(env_value);
	tmp = NULL;
	return (new);
}

void	get_variable(t_shell *shell, char **new, char *str, int *i)
{
	char	*tmp;
	int		j;

	j = *i + 1;
	while ((str[j] && ft_isalnum(str[j])) || str[j] == '_' || str[j] == '?')
		j++;
	tmp = ft_substr(str, *i + 1, j - *i - 1);
	*new = extend_expansor(shell, *new, tmp);
	*i = j - 1;
}

char	*expansor(t_shell *shell, char *str, int i, int j)
{
	char	*new;
	int		quotes;
	int		double_quotes;

	(void)j;
	new = ft_strdup("");
	quotes = 1;
	double_quotes = 1;
	while (str[++i])
	{
		if (str[i] == '\'')
			quotes = !quotes;
		if (str[i] == '\"')
			double_quotes = !double_quotes;
		if ((!double_quotes || quotes) && str[i] == '$' && str[i + 1] && str[i
				+ 1] != ' ' && str[i + 1] != '$')
		{
			get_variable(shell, &new, str, &i);
		}
		else
			new = ft_strjoin_char(new, str[i]);
	}
	return (new);
}
