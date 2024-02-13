/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:41 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/13 17:34:59 by bautrodr         ###   ########.fr       */
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
	size_t		len;
	char		*var_name;
	t_env_lst	*tmp;

	start = ++(*token);
	if (**(token) == '?')
	{
		var_name = ft_itoa(g_exit_status);
		return (var_name);
	}
	else
	{
		len = *token - start;
		var_name = malloc(len + 1);
		ft_strlcpy(var_name, start, len + 1);
		var_name[len] = '\0';
	}
	tmp = find_env_node(shell->paths->env_lst, var_name);
	if (tmp)
		return (ft_strdup(tmp->name));
	return (var_name);
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

char *expansor(t_shell *shell, char *line)
{
	char	**argv;
	char	*expanded;
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	argv = echo_split(line, ' ');
	while (argv[i])
	{
		if (is_variable(argv[i]))
		{
			expanded = ft_expand_var(argv[i], shell);
			if (i < arg_counter(argv))
				result = ft_strjoin(expanded, " ");
			else
				result = ft_strjoin(result, expanded);
			printf("result -> %s\n", result);
			//result = ft_strjoin(result, expanded);
			free(expanded);
		}
		i++;
	}
	return (result);
}
