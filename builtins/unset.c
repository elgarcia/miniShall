/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:04:34 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/19 13:23:24 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	remove_env_var(t_env_lst *env_lst, char *name)
{
	t_env_lst *current;

	current = env_lst;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, name))
		{
			env_lst = current->next;
			free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			break ;
		}
		current = current->next;
	}
}

void	ft_unset(t_paths *paths, char *name)
{
	remove_env_var(paths->env_lst, name);
	remove_env_var(paths->export_env_lst, name);
}
