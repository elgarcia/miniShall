/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:15:48 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 17:44:52 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

t_env_lst	*insert_sorted(t_env_lst *head, char *name, char *value, int equal)
{
	t_env_lst	*new_node;
	t_env_lst	*current;

	new_node = malloc(sizeof(t_env_lst));
	if (!new_node)
	{
		perror("Error allocating memory for the new node");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->equal = equal;
	new_node->next = NULL;
	if (!head || ft_strcmp(name, head->name) < 0)
	{
		new_node->next = head;
		return (new_node);
	}
	current = head;
	while (current->next && ft_strcmp(name, current->next->name) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (head);
}

void	free_env_lst(t_env_lst *head)
{
	t_env_lst	*current;
	t_env_lst	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	sort_env_list(t_env_lst **head)
{
	t_env_lst	*sorted;
	t_env_lst	*current;
	t_env_lst	*next;

	sorted = NULL;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		sorted = insert_sorted(sorted, current->name, current->value,
				current->equal);
		current = next;
	}
	free_env_lst(*head);
	*head = sorted;
}
