/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:41 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/14 15:30:47 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

t_process	*find_env_process(t_process *process_lst)
{
	t_process	*tmp;

	tmp = process_lst;
	while (tmp)
	{
		if (!ft_strcmp(process_lst->process, tmp->process))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

static char *find_variable(char **token, t_shell *shell)
{
	char		*start;
	char		*var_name;
	t_env_lst	*tmp;

	start = ++(*token);
	if (**(token) == '?')
	{
		var_name = ft_itoa(g_exit_status);
		return (var_name);
	}
	else
		var_name = *token;
	tmp = find_env_node(shell->paths->env_lst, var_name);
	if (tmp)
		return (ft_strdup(tmp->value));
	return (ft_strdup(*token));
}

char	*ft_expand_var(char *variable_name, t_shell *shell)
{
	char	*token;
	char	*result;

	token = variable_name;
	result = NULL;
	while (*token)
	{
		if (*token == '$' && *(token + 1) != '\0')
			result = find_variable(&token, shell);
		token++;
	}
	return (result);
}

static int	is_variable(char *token)
{
	return (token[0] == '$' && token[1] != '\0');
}

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
	free(s1);
	return (new);
}

char *expansor(t_shell *shell, char *line)
{
	char	**argv;
	char	*expanded;
	char	*result;
	int		i;

	i = 0;
	argv = echo_split(line, ' ');
	result = ft_strdup("");
	while (argv[i])
	{
		remove_char(argv[i], '\"');
		if (is_variable(argv[i]))
		{
			expanded = ft_expand_var(argv[i], shell);
			result = ft_strjoinfree(result, expanded);
			if (i + 1 < arg_counter(argv))
				result = ft_strjoinfree(result, " ");
			free(expanded);
		}
		else
		{
			result = ft_strjoinfree(result, argv[i]);
			if (i + 1 < arg_counter(argv))
				result = ft_strjoinfree(result, " ");
		}
		i++;
	}
	ft_free(argv, arg_counter(argv));
	return (result);
}
