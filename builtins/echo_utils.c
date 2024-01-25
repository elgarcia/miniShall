/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:24:28 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/25 12:25:14 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	quotes_counter(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quotes++;
		else if (str[i] == '\"')
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (1);
	return (0);
}

int	remove_char(char *str, char c)
{
	int	new;
	int	i;

	new = 0;
	i = 0;
	if (!quotes_counter(str))
	{
		while (str[i])
		{
			if (str[i] && str[i] != c)
				str[new ++] = str[i];
			i++;
		}
		str[new] = 0;
	}
	else
	{
		ft_fprintf(2, "Syntax Error!");
		return (1);
	}
	return (0);
}

void	handle_exit_status(char **token)
{
	ft_putnbr_fd(g_exit_status, 1);
	(*token) += 2;
}

void	handle_variable(char **token, t_paths *paths)
{
	char		*start;
	size_t		len;
	char		*var_name;
	t_env_lst	*tmp;

	start = ++(*token);
	while (**token && (isalnum(**token) || **token == '_'))
		(*token)++;
	len = *token - start;
	var_name = malloc(len + 1);
	ft_strlcpy(var_name, start, len + 1);
	var_name[len] = '\0';
	tmp = find_env_node(paths->env_lst, var_name);
	if (tmp)
		ft_putstr_fd(tmp->value, 1);
	free(var_name);
}
