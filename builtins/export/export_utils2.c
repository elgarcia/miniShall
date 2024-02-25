/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 17:44:22 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	add_export_node(t_paths *paths, char *name, char *value, int equal)
{
	t_env_lst	*existing_node_export;

	existing_node_export = find_env_node(paths->export_env_lst, name);
	if (existing_node_export != NULL)
	{
		if (value[0] != '\0' || equal >= 0)
		{
			free(existing_node_export->value);
			existing_node_export->value = ft_strdup(value);
			existing_node_export->equal = 1;
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
		if (value[0] != '\0' || equal == 1)
			add_env_variable(paths, name, value, equal);
	}
}

void	update_existing_node(t_paths *paths, char *name, char *value)
{
	char		*tmp_name;
	t_env_lst	*current;
	char		*new_value;

	tmp_name = ft_substr(name, 0, ft_strlen(name) - 1);
	current = find_env_node(paths->export_env_lst, tmp_name);
	if (current != NULL)
	{
		new_value = ft_strjoin(current->value, value);
		free(current->value);
		current->value = new_value;
		add_env_variable(paths, tmp_name, new_value, 1);
	}
	else
		add_export_node(paths, tmp_name, value, 1);
	free(tmp_name);
}

void	process_export_variable(t_paths *paths, char *name, char *value, int equal)
{
	if (name[0] != '\0')
		add_export_node(paths, name, value, equal);
	else
	{
		g_exit_status = 1;
		ft_fprintf(2, "Not a valid identifier\n");
	}
}

int	is_last_char_plus(const char *str)
{
	int	len;

	len = ft_strlen(str);
	return (len > 0 && str[len - 1] == '+');
}

void	update_or_process(t_paths *paths, char *name, char *value, int equal)
{
	if (is_last_char_plus(name))
		update_existing_node(paths, name, value);
	else
		process_export_variable(paths, name, value, equal);
	free(name);
	free(value);
}
