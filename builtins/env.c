/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:19:12 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:28:50 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	ft_env(t_paths *paths, char **argv)
{
	int	argc;

	argc = arg_counter(argv);
	if (argc > 1)
	{
		paths->last_exit_status = 127;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	print_env_list(paths->env_lst);
	paths->last_exit_status = 0;
}
