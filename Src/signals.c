/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:40:44 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

extern int g_pid;

void	readline_newline(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	proc_handle_signal(int signo)
{
	if (!kill(g_pid, signo))
	{
		if (signo == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		else if (signo == SIGINT)
			ft_putchar_fd('\n', 1);
	}
	else if (signo == SIGINT)
		readline_newline();
}

void	handle_signal(int signo)
{
	if ((signo == SIGINT || signo == SIGQUIT) && g_pid != 0)
		proc_handle_signal(signo);
	else
	{
		if (signo == SIGINT)
			readline_newline();
		else if (signo == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}
