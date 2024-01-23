/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:20:36 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:38:21 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	extract_name_value(char *arg, char **name, char **value)
{
	char	*equals_sign;
	int		equal;

	equal = 0;
	equals_sign = ft_strchr(arg, '=');
	if (equals_sign != NULL)
	{
		*name = ft_substr(arg, 0, equals_sign - arg);
		*value = ft_strdup(equals_sign + 1);
		equal = 1;
	}
	else
	{
		*name = ft_strdup(arg);
		*value = ft_strdup("");
	}
	return (equal);
}

void	add_env_variable(t_paths *paths, char *name, char *value, int equal)
{
	t_env_lst	*existing_node_env;

	existing_node_env = find_env_node(paths->env_lst, name);
	if (existing_node_env != NULL)
	{
		if (value[0] != '\0')
		{
			free(existing_node_env->value);
			existing_node_env->value = ft_strdup(value);
		}
		else
			existing_node_env->equal = 1;
	}
	else
		add_env_node(paths->env_lst, name, value, equal);
}

void	add_export_node(t_paths *paths, char *name, char *value, int equal)
{
	t_env_lst	*existing_node_export;

	existing_node_export = find_env_node(paths->export_env_lst, name);
	if (existing_node_export != NULL)
	{
		if (value[0] != '\0')
		{
			free(existing_node_export->value);
			existing_node_export->value = ft_strdup(value);
			add_env_variable(paths, name, value, equal);
		}
		else
			existing_node_export->equal = 1;
	}
	else
	{
		add_env_node(paths->export_env_lst, name, value, equal);
		if (value[0] != '\0')
			add_env_variable(paths, name, value, equal);
	}
}
