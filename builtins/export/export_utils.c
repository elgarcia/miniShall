/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:20:36 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 19:53:09 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_result(const char *target_chars, const char *str, size_t new_len,
		size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = (char *)malloc_safe(new_len + 1, 1);
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

char	*str_clean_str(const char *str, const char *target_chars, size_t i)
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
	result = get_result(target_chars, str, new_len, len);
	return (result);
}

void	clean_name_value(char *arg, char **name, char **value,
		char *equals_sign)
{
	char	*tmp;

	if (equals_sign != NULL)
	{
		tmp = ft_substr(arg, 0, equals_sign - arg);
		*name = str_clean_str(tmp, "\"\'", 0);
		free(tmp);
		tmp = ft_strdup(equals_sign + 1);
		*value = str_clean_str(tmp, "\"", 0);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup(arg);
		*name = str_clean_str(tmp, "\"\'", 0);
		free(tmp);
		tmp = ft_strdup("");
		*value = str_clean_str(tmp, "\'\"", 0);
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
		paths->env_lst = add_env_node(paths->env_lst, name, value, equal);
}
