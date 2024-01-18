/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:04:46 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/18 14:13:20 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

t_env_lst	*insert_sorted(t_env_lst *head, char *name, char *value)
{
	t_env_lst	*new_node;
	t_env_lst	*current;

	new_node = malloc(sizeof(t_env_lst));
	if (!new_node)
	{
		perror("Error al asignar memoria para el nuevo nodo");
		exit(EXIT_FAILURE);
	}
	new_node->name = strdup(name);
	new_node->value = strdup(value);
	new_node->next = NULL;
	if (!head || strcmp(name, head->name) < 0)
	{
		new_node->next = head;
		return (new_node);
	}
	current = head;
	while (current->next && strcmp(name, current->next->name) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (head);
}

void	sort_env_list(t_env_lst **head)
{
	t_env_lst	*sorted;
	t_env_lst	*current;
	t_env_lst	*next;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	sorted = NULL;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		sorted = insert_sorted(sorted, current->name, current->value);
		current = next;
	}
	*head = sorted;
}

void	print_export(t_env_lst *env_lst, int declare_x)
{
	t_env_lst	*current;

	//sort_env_list(&env_lst);
	current = env_lst;
	while (current != NULL)
	{
		if (declare_x)
			printf("declare -x %s", current->name);
		else
			printf("%s", current->name);
		if (current->name && current->equal == 1 && current->value[0] == '\0')
			printf("=\"\"");
		else if (current->value[0] != '\0')
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

int	extract_name_value(char *arg, char **name, char **value)
{
	char	*equals_sign;
	int		equal;

	equal = 0;
	equals_sign = ft_strchr(arg, '=');
	if (equals_sign != NULL)
	{
		*name = ft_substr(arg, 0, equals_sign - arg);
		*value = ft_strdup(equals_sign + 1);
		equal = 1;
	}
	else
	{
		*name = ft_strdup(arg);
		*value = ft_strdup("");
	}
	return (equal);
}

void	ft_export(t_paths *paths, char **argv, int i) //aca funciona bien
{
	char		*name;
	char		*value;
	int			equal;
	t_env_lst	*existing_node_export;
	t_env_lst	*existing_node_env;

	if (!argv[1])
		print_export(paths->export_env_lst, 1);
	else
	{
		while (argv[i])
		{
			equal = extract_name_value(argv[i], &name, &value);
			if (name[0] != '\0')
			{
				existing_node_export = find_env_node(paths->export_env_lst,
						name);
				if (existing_node_export != NULL)
				{
					if (value[0] != '\0')
					{
						free(existing_node_export->value);
						existing_node_export->value = ft_strdup(value);
					}
					else
						existing_node_export->equal = 1;
				}
				else
				{
					add_env_node((paths->export_env_lst), name, value, equal);
					existing_node_env = find_env_node(paths->env_lst, name);
					if (existing_node_env == NULL && value[0] != '\0')
						add_env_node((paths->env_lst), name, value, equal);
				}
			}
			free(name);
			free(value);
			i++;
		}
	}
}
