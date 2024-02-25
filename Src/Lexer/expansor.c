/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 16:35:23 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*find_variable(char **token, t_shell *shell)
{
	char		*var_name;
	t_env_lst	*tmp;

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

char	*expand_single_var(char **variable_name, t_shell *shell)
{
	char	*variable;
	char	*tmp;
	int		i;

	i = 0;
	variable = malloc(sizeof(char) * ft_strlen(*variable_name));
	if (!variable)
		return (NULL);
	(*variable_name)++;
	while (**variable_name && **variable_name != '$')
	{
		variable[i++] = **variable_name;
		(*variable_name)++;
	}
	variable[i] = '\0';
	tmp = find_variable(&variable, shell);
	free(variable);
	return (tmp);
}

char	*expand_and_join_arguments(t_shell *shell, char **argv)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (argv[i])
	{
		if (i == 0 || (i > 0 && !ft_strnstr(argv[i - 1], "-", 1)))
			remove_quotes(argv[i]);
		if (argv[i][0] == '$' && argv[1][1] != '\0')
			result = get_var_res(shell, result, argv, i);
		else
		{
			result = ft_strjoinfree(result, argv[i]);
			if (result[0] == '\"' || result[0] == '\'')
				remove_char(result, result[0]);
		}
		if (i + 1 < arg_counter(argv))
			result = ft_strjoinfree(result, " ");
		i++;
	}
	return (result);
}

char	*expansor(t_shell *shell, char *line)
{
	char	**argv;
	char	*result;

	argv = ft_split(line, ' ');
	if (is_builting_exp(argv[0]))
	{
		result = expand_and_join_arguments(shell, argv);
		ft_free(argv, arg_counter(argv));
		return (result);
	}
	ft_free(argv, arg_counter(argv));
	return (ft_strdup(line));
}
