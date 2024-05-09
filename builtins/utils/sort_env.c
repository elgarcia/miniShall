/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:15:48 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/09 19:37:32 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*insert_sorted(t_env_lst *head, char *name, char *value, int equal)
{
	t_env_lst	*new_node;
	t_env_lst	*current;

	new_node = malloc_safe(sizeof(t_env_lst), 1);
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

void sort_env_list(t_env_lst **head) {
  t_env_lst *sorted = NULL;
  t_env_lst *current = *head;
  t_env_lst *next;

  // Iterate through the original list
  while (current != NULL) {
    next = current->next;

    // Insert current element into sorted list
    sorted = insert_sorted(sorted, current->name, current->value, current->equal);

    // Move to the next element in the original list
    current = next;
  }

  // Free the original list (optional)
  free_env_lst(*head);

  // Update the head pointer to point to the sorted list
  *head = sorted;
}
