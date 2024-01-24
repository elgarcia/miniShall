/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:19:12 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/24 09:30:51 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	ft_env(t_paths *paths, char **argv)
{
	int	argc;

	argc = arg_counter(argv);
	if (argc > 1)
	{
		g_exit_status = 127;
		ft_fprintf(2, "env: %s: No such file or directory\n", argv[1]);
		return ;
	}
	print_env_list(paths->env_lst);
	g_exit_status = 0;
}
