/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:20:36 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/24 16:01:47 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

char	*str_clean_str(const char *str, const char *target_chars, size_t i,
		size_t j)
{
	size_t	len;
	size_t	new_len;
	char	*result;

	if (!str || !target_chars)
		return (NULL);
	len = ft_strlen(str);
	new_len = 0;
	i = 0;
	while (i < len)
	{
		if (!ft_strchr(target_chars, str[i]))
			++new_len;
		++i;
	}
	result = (char *)malloc(new_len + 1);
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		if (!ft_strchr(target_chars, str[i]))
			result[j++] = str[i];
		++i;
	}
	result[j] = '\0';
	return (result);
}

void	clean_name_value(char *arg, char **name, char **value,
		char *equals_sign)
{
	char	*tmp;

	if (equals_sign != NULL)
	{
		tmp = ft_substr(arg, 0, equals_sign - arg);
		*name = str_clean_str(tmp, "\"\'", 0, 0);
		free(tmp);
		tmp = ft_strdup(equals_sign + 1);
		*value = str_clean_str(tmp, "\"", 0, 0);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup(arg);
		*name = str_clean_str(tmp, "\"\'", 0, 0);
		free(tmp);
		tmp = ft_strdup("");
		*value = str_clean_str(tmp, "\'\"", 0, 0);
		free(tmp);
	}
}

int	extract_name_value(char *arg, char **name, char **value)
{
	char	*equals_sign;
	int		equal;

	equal = 0;
	equals_sign = ft_strchr(arg, '=');
	if (equals_sign != NULL)
	{
		clean_name_value(arg, name, value, equals_sign);
		equal = 1;
	}
	else
		clean_name_value(arg, name, value, equals_sign);
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
		{
			existing_node_export->value = ft_strdup("");
			existing_node_export->equal = 1;
		}
	}
	else
	{
		add_env_node(paths->export_env_lst, name, value, equal);
		if (value[0] != '\0')
			add_env_variable(paths, name, value, equal);
	}
}
