/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/15 14:47:56 by bautrodr         ###   ########.fr       */
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

static char	*find_variable(char **token, t_shell *shell)
{
	char		*var_name;
	t_env_lst	*tmp;

	//	char		*start;
	// start = ++(*token);
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

char *expand_single_var(char **variable_name, t_shell *shell)
{
    char *variable;
    char *tmp;
    int i = 0;

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
    return tmp;
}

char *ft_expand_var(char *variable_name, t_shell *shell)
{
    char *result;
    char *tmp;

    result = ft_strdup("");
    while (*variable_name)
    {
        if (*variable_name == '$' && *(variable_name + 1) != '\0')
        {
            tmp = expand_single_var(&variable_name, shell);
            result = ft_strjoinfree(result, tmp);
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

char	**split_arguments(char *line, char delimiter)
{
	return (echo_split(line, delimiter));
}

void	remove_quotes(char *arg)
{
	if (arg[0] == '\"' || (arg[0] == '\'' && arg[1] != '$'))
		remove_char(arg, arg[0]);
}

char	*expand_and_join_arguments(t_shell *shell, char **argv)
{
	char	*result;
	int		i;
	char	*expanded;

	result = ft_strdup("");
	i = 0;
	while (argv[i])
	{
		remove_quotes(argv[i]);
		if (is_variable(argv[i]))
		{
			expanded = ft_expand_var(argv[i], shell);
			result = ft_strjoinfree(result, expanded);
			free(expanded);
		}
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

	argv = split_arguments(line, ' ');
	result = expand_and_join_arguments(shell, argv);
	ft_free(argv, arg_counter(argv));
	return (result);
}
