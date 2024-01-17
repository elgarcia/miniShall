/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:23:33 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/17 12:02:07 by bautrodr         ###   ########.fr       */
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
