/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:55:19 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:07:05 by bautrodr         ###   ########.fr       */
/*   Updated: 2024/01/18 20:07:13 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

static void	extend_echo(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] && argv[i][0])
			write(1, " ", 1);
		i++;
	}
}


int ft_echo(char **args)
{
    int i = 1;
    int new_line = 1;

    while (args[i] && args[i][0] == '-' && args[i][1] == 'n' && !args[i][2]) {
        new_line = 0;
        i++;
    }

    while (args[i]) {
        if (args[i][0] == '\'' || args[i][0] == '\"') {
            char quote_char = args[i][0];
            printf("%s", args[i] + 1);
            i++;
            while (args[i] && args[i][0] != quote_char) {
                printf(" %s", args[i]);
                i++;
            }
            if (args[i] && args[i][0] == quote_char)
                printf("%s", args[i] + 1);
        } else {
            printf("%s", args[i]);
        }

        i++;
        if (args[i])
            printf(" ");
    }

    if (new_line)
        printf("\n");

    return 0;
}

int ft_echo(char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == '\0')
			flag = 1;
		else
			break ;
		i++;
	}
	extend_echo(argv, i);
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
