/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:51:37 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/25 17:54:21 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	g_exit_status = 0;

void	change_shell(t_shell *shell)
{
	char	*tmp;

	tmp = ft_strjoin(shell->paths->pwd, "/minishell");
	add_export_node(shell->paths, "SHELL", tmp, 1);
	free(tmp);
}

void print_banner()
{
	printf("\n");
	printf(GREEN_TEXT "███╗   ███╗██╗███╗   ██╗██╗███████╗" RESET_TEXT);
	printf(GREEN_TEXT "	██╗  ██╗ █████╗ ██╗     ██╗	  \n" RESET_TEXT);
	printf(GREEN_TEXT "████╗ ████║██║████╗  ██║██║██╔════╝" RESET_TEXT);
	printf(GREEN_TEXT "	██║  ██║██╔══██╗██║     ██║     \n" RESET_TEXT);
	printf(GREEN_TEXT "██╔████╔██║██║██╔██╗ ██║██║███████╗" RESET_TEXT);
	printf(GREEN_TEXT "	███████║███████║██║     ██║     \n" RESET_TEXT);
	printf(GREEN_TEXT "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║" RESET_TEXT);
	printf(GREEN_TEXT "	██╔══██║██╔══██║██║     ██║		\n" RESET_TEXT);
	printf(GREEN_TEXT "██║ ╚═╝ ██║██║██║ ╚████║██║███████║" RESET_TEXT);
	printf(GREEN_TEXT " ██║  ██║██║  ██║███████╗███████╗\n" RESET_TEXT);
	printf(GREEN_TEXT "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝" RESET_TEXT);
	printf(GREEN_TEXT " ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝\n" RESET_TEXT);
	printf("\n");
}

void	extend(t_shell *new, char *line)
{
	char	*new_line;

	if (line == NULL)
	{
		printf("Exit\n");
		ft_exit(new, line);
	}
	if (line[0] != 0)
	{
		add_to_history(new, line);
		add_history(line);
		if (ft_strnstr(line, "exit", 5))
			return (ft_exit(new, line));
		new_line = expansor(new, line, -1, 0);
		if (input_parser(new_line, new) != -1)
		{
			add_history(line);
			init_pikes(&new);
			exec_process(new);
			free_pikes(&new);
		}
		free(new_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;
	char	*line;
	char	*prompt;

	(void)argv;
	if (argc == 1)
	{
		print_banner();
		init_minishell(&new, envp);
		change_shell(new);
		while (42)
		{
			set_signals(0);
			prompt = get_prompt(new);
			printf(BLUE_TEXT "%s" RESET_TEXT, prompt);
			line = readline(GREEN_TEXT " minishall > " RESET_TEXT);
			if (quotes_counter(line))
				printf("Quotes opened!\n");
			else
				extend(new, line);
			free(prompt);
			free(line);
		}
	}
	else
		ft_fprintf(2, "Too many arguments\n");
}
