/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/01 18:01:53 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"
#include <termios.h>

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

void	set_signals(int mode)
{
	struct sigaction	sa;
	struct termios		term;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	if (mode == 0)
		sa.sa_handler = &handle_signal;
	else if (mode == 1)
	{
		term.c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
		sa.sa_handler = SIG_DFL;
	}
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
