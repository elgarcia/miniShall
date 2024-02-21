/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/20 20:25:28 by bautrodr         ###   ########.fr       */
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

char	*ft_expand_var(char *variable_name, t_shell *shell)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (variable_name[i])
	{
		if (variable_name[i] == '$' && variable_name[i + 1] != '\0')
		{
			tmp = expand_single_var(&variable_name, shell);
			printf("tmp: %s\n", tmp);
			result = ft_strjoinfree(result, tmp);
			free(tmp);
		}
		else
			result = ft_strjoinfree(result, ft_substr(variable_name, i, 1));
			i++;
	}
	return (result);
}

static int	is_variable(char *token)
{
	return (token[0] == '$' && token[1] != '\0');
}

void	remove_quotes(char *arg)
{
	if (arg[0] == '\"' || (arg[0] == '\'' && arg[1] != '$'))
		remove_char(arg, arg[0]);
}

char	*get_var_res(t_shell *shell, char *result, char *argv)
{
	char	*expanded;

	printf("result: %s\n", result);
	expanded = ft_expand_var(argv, shell);
	result = ft_strjoinfree(result, expanded);
	free(expanded);
	return (result);
}

char	*expand_and_join_arguments(t_shell *shell, char **argv)
{
	char	*result;
	int		i;
	int		j;

	result = ft_strdup("");
	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			printf("argv[i][j]: %s\n", &argv[i][j]);
			if (is_variable(&argv[i][j]))
			{
				result = get_var_res(shell, result, &argv[i][j]);
				break;
			}
			else
				result = ft_strdup(argv[i]);
			j++;
		}
		printf("result: -->> %s\n", result);
		if (i + 1 < arg_counter(argv))
			result = ft_strjoinfree(result, " ");
		if (argv[i + 1])
			result = ft_strjoinfree(ft_strdup(argv[i]), result);
		i++;
	}
	return (result);
}

char	*expansor(t_shell *shell, char *line)
{
	char	**argv;
	char	*result;

	argv = echo_split(line, ' ');
	result = expand_and_join_arguments(shell, argv);
	ft_free(argv, arg_counter(argv));
	printf("expanded: %s\n", result);
	return (result);
}
