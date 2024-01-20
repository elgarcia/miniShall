/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:04:34 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/20 12:45:52 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void free_env_node(t_env_lst *node)
{
    free(node->name);
    free(node->value);
    free(node);
}

void remove_node(t_env_lst **head, char *name)
{
    t_env_lst *current = *head;
    t_env_lst *prev = NULL;

    while (current != NULL)
    {
        if (ft_strcmp(current->name, name) == 0)
        {
            if (prev != NULL)
                prev->next = current->next;
            else
                *head = current->next;
            free_env_node(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void ft_unset(t_paths *paths, char **argv)
{
    int i = 1;

    while (argv[i] != NULL)
    {
        remove_node(&(paths->export_env_lst), argv[i]);
        remove_node(&(paths->env_lst), argv[i]);
        i++;
    }
}
