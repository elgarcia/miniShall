/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/22 17:01:37 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

extern int g_pid;

void	readline_newline(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	proc_handle_signal(int signo)
{
	close(g_pid);
	kill(g_pid, signo);
	readline_newline();
}

void	handle_signal(int signo)
{
	if ((signo == SIGINT || signo == SIGQUIT) && g_pid != 0)
		proc_handle_signal(signo);
	else
	{
		if (signo == SIGINT || signo == SIGQUIT)
			readline_newline();
	}
}
