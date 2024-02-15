/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/15 14:44:19 by bautrodr         ###   ########.fr       */
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
//	char		*start;
	char		*var_name;
	t_env_lst	*tmp;

	//start = ++(*token);
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
	char	*result;
	char	*variable;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	while (*variable_name)
	{
		if (*variable_name == '$' && *(variable_name + 1) != '\0')
		{
			i = 0;
			variable_name++;
			variable = malloc(sizeof(char) * ft_strlen(variable_name));
			while (*variable_name && *variable_name != '$')
			{
				variable[i++] = *variable_name;
				variable_name++;
			}
			variable[i] = '\0';
			tmp = find_variable(&variable, shell);
			result = ft_strjoinfree(result, tmp);
			free(variable);
			free(tmp);
		}
		else
			variable_name++;
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
	argv = echo_split(line, ' ');
	result = ft_strdup("");
	while (argv[i])
	{
		if (argv[i][0] == '\"' || (argv[i][0] == '\'' && argv[i][1] != '$'))
			remove_char(argv[i], argv[i][0]);
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
			if (argv[i][0] == '\"' || (argv[i][0] == '\''))
				remove_char(argv[i], argv[i][0]);
			result = ft_strjoinfree(result, argv[i]);
			if (i + 1 < arg_counter(argv))
				result = ft_strjoinfree(result, " ");
		}
		i++;
	}
	ft_free(argv, arg_counter(argv));
	return (result);
}
