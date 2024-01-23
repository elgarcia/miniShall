/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:23:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/19 17:29:01 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	delete_env_value(t_env_lst *lst, char *key)
{
	t_env_lst	*current;

	current = lst;
	if (!key)
		return ;
	while (current)
	{
		if (ft_strncmp(current->name, key, ft_strlen(key)) == 0)
		{
			ft_lstdelone_env(current);
			break ;
		}
		current = current->next;
	}
	current = current->next;
}

t_env_lst	*duplicate_env_node(const t_env_lst *node)
{
	t_env_lst	*new_node;

	new_node = malloc(sizeof(t_env_lst));
	if (!new_node)
	{
		perror("Error al asignar memoria para el nuevo nodo");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_strdup(node->name);
	new_node->value = ft_strdup(node->value);
	new_node->next = NULL;
	return (new_node);
}

t_env_lst	*duplicate_lst(const t_env_lst *head)
{
	t_env_lst	*new_head;
	t_env_lst	*current;

	if (!head)
		return (NULL);
	new_head = duplicate_env_node(head);
	current = new_head;
	while (head->next)
	{
		head = head->next;
		current->next = duplicate_env_node(head);
		current = current->next;
	}
	return (new_head);
}

int	arg_counter(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
