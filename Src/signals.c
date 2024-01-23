/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 15:13:08 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

extern int g_pid;

void	readline_newline(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	proc_handle_signal(int signo)
{
	kill(g_pid, signo);
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
}

void	handle_signal(int signo)
{
	if ((signo == SIGINT) && g_pid != 0)
	{
		proc_handle_signal(signo);
		g_pid = 0;
	}
	else
	{
		if (signo == SIGINT)
			readline_newline();
	}
}
