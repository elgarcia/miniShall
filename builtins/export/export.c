/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:04:46 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/08 15:47:25 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

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
	if (argv && !ft_isalpha(argv[0]) && argv[0] != '\"' && argv[0] != '\''
		&& argv[0] != '_')
	{
		g_exit_status = 1;
		return (ft_fprintf(2, "export: `%s': not a valid identifier\n", argv));
	}
	g_exit_status = 0;
	return (0);
}

int	contains_symbols(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '+')
		len--;
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '\"'
			&& str[i] != '\'' && i < len)
			return (1);
		i++;
	}
	return (0);
}

void	handle_export_variables(t_paths *paths, char **argv, int i)
{
	char	*name;
	char	*value;
	int		equal;

	while (argv[i] && argv[i][0])
	{
		if (check_var(argv[i]))
			return ;
		equal = extract_name_value(argv[i], &name, &value);
		if (contains_symbols(name))
		{
			g_exit_status = 1;
			ft_fprintf(2, "export: `%s=%s\': not a valid identifier\n", name,
				value);
			return ;
		}
		update_or_process(paths, name, value, equal);
		i++;
	}
	sort_env_list(&(paths->export_env_lst));
	sort_env_list(&(paths->env_lst));
	g_exit_status = 0;
}

void	ft_export(t_paths *paths, char **argv, int i)
{
	if (!argv[1])
	{
		print_export(paths->export_env_lst, 1);
		g_exit_status = 0;
	}
	else
		handle_export_variables(paths, argv, i);
}
