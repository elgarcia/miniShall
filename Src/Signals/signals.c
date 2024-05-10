/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/10 14:14:28 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structures.h"
#include <termios.h>

int g_exit_status = 0;

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

    g_exit_status = 0;
	if (mode == 0)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		tcgetattr(0, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
	}
	else if (mode == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		tcgetattr(0, &term);
		term.c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
	}
	else if (mode == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
