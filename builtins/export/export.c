/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:04:46 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/10 16:46:16 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (ft_fprintf(2, "export: `%s': not a valid identifier\n", argv));
	}
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

int	handle_export_variables(t_paths *paths, char **argv)
{
	char	*name;
	char	*value;
	int		equal;
	int		i;

	i = 1;
	while (argv[i] && argv[i][0])
	{
		if (check_var(argv[i]))
			return (1);
		equal = extract_name_value(argv[i], &name, &value);
		if (contains_symbols(name))
		{
			ft_fprintf(2, "export: `%s=%s\': not a valid identifier\n", name,
				value);
			return (1);
		}
		update_or_process(paths, name, value, equal);
		i++;
	}
	return (0);
}

int	ft_export(t_paths *paths, char **argv)
{
	int	ret;

	sort_env_list(&(paths->export_env_lst));
	if (!argv[1])
	{
		print_export(paths->export_env_lst, 1);
		ret = 0;
	}
	else
		ret = handle_export_variables(paths, argv);
	return (ret);
}
