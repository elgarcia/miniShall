/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:26:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 17:36:44 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*find_env_node(t_env_lst *env_lst, char *key)
{
	int			name_len;
	t_env_lst	*tmp;

	tmp = env_lst;
	if (!tmp)
		return (NULL);
	name_len = ft_strlen(env_lst->name);
	while (tmp != NULL && ft_strncmp(tmp->name, key, name_len) != 0)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	free_str_array(char **str_array)
{
	int	i;

	if (str_array)
	{
		i = 0;
		while (str_array[i])
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
	}
}

void	update_pwd_variables(t_paths *paths, char *new_pwd)
{
	t_env_lst	*pwd_node;
	t_env_lst	*old_pwd_node;

	old_pwd_node = find_env_node(paths->env_lst, "OLDPWD");
	if (old_pwd_node)
	{
		free(old_pwd_node->value);
		old_pwd_node->value = get_env(NULL, "PWD", paths->env_lst);
	}
	pwd_node = find_env_node(paths->env_lst, "PWD");
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(new_pwd);
	}
}

char	*resolve_single_component(char *current_path, char *component)
{
	char	*temp;

	temp = NULL;
	if (ft_strncmp(component, "...", 3) == 0)
		return (NULL);
	else if (ft_strcmp(component, "..") == 0)
		temp = get_previous_dir(current_path);
	else if (ft_strcmp(component, ".") == 0)
		temp = ft_strdup(current_path);
	else
		temp = join_paths(current_path, component);
	return (temp);
}

char	*resolve_parent_references(char *current_dir, char *target)
{
	char	**target_components;
	char	*result;
	int		i;
	char	*temp;

	target_components = ft_split(target, '/');
	result = ft_strdup(current_dir);
	i = 0;
	while (target_components[i] != NULL)
	{
		temp = resolve_single_component(result, target_components[i]);
		if (!temp)
		{
			free(result);
			free_str_array(target_components);
			return (temp);
		}
		free(result);
		result = temp;
		i++;
	}
	free_str_array(target_components);
	return (result);
}
