/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:28:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/10 13:37:55 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*add_env_node(t_env_lst *head, char *name, char *value, int equal)
{
	t_env_lst	*new_node;
	t_env_lst	*current;

	new_node = malloc_safe(sizeof(t_env_lst), 1);
	new_node->name = ft_strdup(name);
	if (!value)
		new_node->value = ft_strdup("");
	else
		new_node->value = ft_strdup(value);
	if (equal == 1)
		new_node->equal = 1;
	new_node->next = NULL;
	if (head == NULL)
		return (new_node);
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (head);
}

void	fill_init_env_list(t_paths *paths, char **envp, int equal)
{
	int			i;
	t_env_lst	*head;
	char		*name;
	char		*value;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		if (ft_strlenchr(envp[i], '='))
			equal = 1;
		else
			equal = 0;
		name = ft_substr(envp[i], 0, ft_strlen(envp[i])
				- ft_strlen(ft_strchr(envp[i], '=')));
		value = ft_substr(envp[i], ft_strlen(envp[i])
				- ft_strlen(ft_strchr(envp[i], '=')) + 1, ft_strlen(envp[i]));
		head = add_env_node(head, name, value, equal);
		free(name);
		free(value);
		i++;
	}
	paths->env_lst = head;
}

void	print_env_list(t_env_lst *head)
{
	t_env_lst	*current;

	current = head;
	while (current)
	{
		printf("%s=", current->name);
		if (current->value)
			printf("%s\n", current->value);
		current = current->next;
	}
}

void	ft_lstdelone_env(t_env_lst *lst)
{
	if (!lst)
		return ;
	else
	{
		free(lst->name);
		free(lst->value);
		free(lst);
	}
}

void	ft_lstclear_env(t_env_lst **lst)
{
	t_env_lst	*current;
	t_env_lst	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone_env(current);
		current = next;
	}
	*lst = NULL;
}
