/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:23:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/19 12:23:37 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

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
/*
int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;

	new = (t_shell *)ft_calloc(1, sizeof(t_shell));
	new->paths = malloc(sizeof(t_paths));
	new->paths->pwd = ft_strdup(getenv("PWD"));
	new->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
	new->paths->home = ft_strdup(getenv("HOME"));
	fill_init_env_list(new->paths, envp);
	new->paths->export_env_lst = new->paths->env_lst;
	//exe_command(new->paths, argv, argc);
	print_env_list(new->paths->env_lst);
	delete_env_value(new->paths->env_lst, argv[1]);
	printf("\n\n\n\n");
	print_env_list(new->paths->env_lst);
	//ft_lstclear_env(&new->paths->env_lst);
	free(new->paths->pwd);
	free(new->paths->old_pwd);
	free(new->paths->home);
	free(new->paths);
	free(new);
	return (0);
}*/
