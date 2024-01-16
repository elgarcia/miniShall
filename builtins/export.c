/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:04:46 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/16 11:23:04 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	print_export(t_env_lst *head, int flag)
{
	t_env_lst	*current;

	current = head;
	while (current)
	{
		if (flag == 1)
			printf("declare -x ");
		printf("%s", current->name);
		if (current->value[0] != '\0')
			printf("=\"%s\"\n", current->value);
		current = current->next;
	}
	printf("\n");
}

void	set_export_env(t_paths *paths, char *name, char *value)
{
	add_env_node(paths->export_env_lst, name, value);
}

void	extend_export(t_paths *paths, char *name, char *value)
{

}

void	ft_export(t_paths *paths, char **argv)
{
	char		*name;
	char		*value;
	t_env_lst	*tmp;

	tmp = NULL;
	if (!argv[2]) //cambiar cuando este hecho el bucle del minishall
		print_export(paths->export_env_lst, 1);
	else
	{
		if (ft_strchr(argv[2], '=') != 0)
			name = ft_substr(argv[2], 0, ft_strlen(argv[2]) 
					- ft_strlen(ft_strchr(argv[2], '=')));
		else
			name = ft_strdup(argv[2]);
		value = ft_substr(argv[2], ft_strlen(argv[2])
				- ft_strlen(ft_strchr(argv[2], '=')) + 1, ft_strlen(argv[2]));
		tmp = find_env_node(paths->export_env_lst, name);
		if (value[0] == '\0')
		{
			set_export_env(paths, name, value);
			print_export(paths->export_env_lst, 0);
			return ;
		}
		add_env_node(paths->export_env_lst, name, value);
		free(name);
		free(value);
		print_export(paths->export_env_lst, 0);
	}
}
