/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:28:24 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/15 10:25:55 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/built_ins.h"

t_env_lst	*add_env_node(t_env_lst *head, char *name, char *value)
{
	t_env_lst	*new_node;
	t_env_lst	*current;

	new_node = malloc(sizeof(t_env_lst));
	if (!new_node)
	{
		perror("Error al asignar memoria para el nuevo nodo");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (head == NULL)
		return (new_node);
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (head);
}

void	fill_init_env_list(t_paths *paths, char **envp)
{
	int			i;
	t_env_lst	*head;
	char		*name;
	char		*value;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strlen(envp[i])
				- ft_strlen(ft_strchr(envp[i], '=') + 1));
		value = ft_substr(envp[i], ft_strlen(envp[i])
				- ft_strlen(ft_strchr(envp[i], '=')) + 1, ft_strlen(envp[i]));
		head = add_env_node(head, name, value);
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
		printf("%s", current->name);
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
/*
int	main(int argc, char **argv, char **envp)
{
	t_paths paths;

	fill_init_env_list(&paths, envp);
	//printf("linea 39 = %s\n", envp[39]);
	//printf("largo line 39 hasta el = %ld\n", ft_strlen(ft_strchr(envp[39],
				'=')));
	printf("Lista de entornos:\n");
	print_env_list(paths.env_lst);
	ft_lstclear_env(&paths.env_lst);

	return (0);
}*/
