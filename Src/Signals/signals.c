/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:03 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/25 16:37:47 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"
#include <termios.h>

void	handle_signal(int sig)
{
    char    *prompt;

    prompt = get_prompt();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
        printf(BLUE_TEXT "%s" RESET_TEXT, prompt);
		rl_redisplay();
		g_exit_status = 1;
	}
    free(prompt);
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
	struct termios		term;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
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
