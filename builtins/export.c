/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:04:46 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/24 16:18:30 by bautrodr         ###   ########.fr       */
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
	if (argv && !ft_isalpha(argv[0]) && argv[0] != '\"' && argv[0] != '\'')
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

void	update_existing_node(t_paths *paths, char *name, char *value)
{
	char		*tmp_name;
	t_env_lst	*current;
	char		*new_value;

	tmp_name = ft_substr(name, 0, ft_strlen(name) - 1);
	current = find_env_node(paths->export_env_lst, tmp_name);
	if (current != NULL)
	{
		new_value = ft_strjoin(current->value, value);
		free(current->value);
		current->value = new_value;
		add_env_variable(paths, tmp_name, new_value, 1);
	}
	else
		add_export_node(paths, tmp_name, value, 1);
	free(tmp_name);
}

void	process_export_variable(t_paths *paths, char *name, char *value)
{
	if (name[0] != '\0')
		add_export_node(paths, name, value, 0);
	else
	{
		g_exit_status = 1;
		ft_fprintf(2, "Not a valid identifier\n");
	}
}

int	is_last_char_plus(const char *str)
{
	int	len;

	len = ft_strlen(str);
	return (len > 0 && str[len - 1] == '+');
}

void	handle_export_variables(t_paths *paths, char **argv, int i)
{
	char	*name;
	char	*value;

	while (argv[i])
	{
		if (check_var(argv[i]))
			return ;
		extract_name_value(argv[i], &name, &value);
		if (contains_symbols(name))
		{
			g_exit_status = 1;
			ft_fprintf(2, "export: `%s=%s\': not a valid identifier\n", name,
				value);
			return ;
		}
		if (is_last_char_plus(name))
			update_existing_node(paths, name, value);
		else
			process_export_variable(paths, name, value);
		free(name);
		free(value);
		i++;
	}
	sort_env_list(&(paths->export_env_lst));
	sort_env_list(&(paths->env_lst));
	g_exit_status = 0;
}

/*
int	count_quotes(char **argv, int j)
{
	int	i;
	int	counter_d;
	int	counter_s;
	int	total;

	counter_d = 0;
	counter_s = 0;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'')
				counter_s++;
			if (argv[i][j] == '\"')
				counter_d++;
			j++;
		}
		i++;
	}
	total = counter_d + counter_s;
	if (total % 2 == 0)
		return (0);
	return (1);
}
*/
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
