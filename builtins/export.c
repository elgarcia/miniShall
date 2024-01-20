/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:04:46 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/20 12:32:24 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	print_export(t_env_lst *env_lst, int declare_x)
{
	t_env_lst	*current;

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

int	check_var(char *argv)
{
	if (argv && !ft_isalpha(argv[0]))
		return (printf("export: `%s': not a valid identifier", argv));
	return (0);
}

void	handle_export_variables(t_paths *paths, char **argv, int i)
{
	char	*name;
	char	*value;
	int		equal;

	while (argv[i] && !check_var(argv[i]))
	{
		equal = extract_name_value(argv[i], &name, &value);
		if (name[0] != '\0')
			add_export_node(paths, name, value, equal);
		free(name);
		free(value);
		i++;
	}
	sort_env_list(&(paths->export_env_lst));
	sort_env_list(&(paths->env_lst));
}

void	ft_export(t_paths *paths, char **argv, int i)
{
	if (!argv[1])
		print_export(paths->export_env_lst, 1);
	else
		handle_export_variables(paths, argv, i);
}
