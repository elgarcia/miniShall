/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/05 16:47:57 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
	return ;
}

void	proc_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_exit_status = 131;
	}
	return ;
}

void	set_signals(int mode)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == 0)
		sa.sa_handler = &handle_signal;
	else if (mode == 1)
		sa.sa_handler = &proc_handle_signal;
	sigaction(SIGINT, &sa, NULL);
	if (!mode)
	{
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, NULL);
	}
	sigaction(SIGQUIT, &sa, NULL);
}
