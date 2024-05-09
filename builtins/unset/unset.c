/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:04:34 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/02 13:26:24 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env_lst *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	remove_node(t_env_lst **head, char *name)
{
	t_env_lst	*current;
	t_env_lst	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*head = current->next;
			free_env_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_paths *paths, char **argv)
{
	int	i;
	int	is_valid;

	i = 1;
	is_valid = 0;
	while (argv[i] != NULL)
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			is_valid = 1;
			i++;
			continue ;
		}
		remove_node(&(paths->export_env_lst), argv[i]);
		remove_node(&(paths->env_lst), argv[i]);
		i++;
	}
	if (is_valid)
		g_exit_status = 1;
	else
		g_exit_status = 0;
}
