/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/30 13:32:00 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"
#include <termios.h>

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
	return ;
}

void	set_signals(int mode)
{
	struct termios	term;

	signal(SIGINT, handle_signal);
	if (mode == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		tcgetattr(0, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
	}
	else if (mode == 1)
	{
		signal(SIGQUIT, SIG_DFL);
		tcgetattr(0, &term);
		term.c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
	}
}
