/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:51:37 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/28 13:45:01 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int		g_exit_status = 0;

void	change_shell(t_shell *shell)
{
	char	*tmp;
	int		lvl;
	char	*lvl_str;

	tmp = ft_strjoin(shell->paths->pwd, "/minishell");
	lvl_str = get_env("SHLVL", shell->paths->env_lst);
	lvl = ft_atoi(lvl_str);
	if (!lvl || lvl < 0 || lvl > 999)
		lvl = 0;
	free(lvl_str);
	lvl_str = ft_itoa(lvl + 1);
	replace_envp("SHLVL=", lvl_str, shell->paths->envp);
	add_export_node(shell->paths, "SHLVL", lvl_str, 1);
	add_export_node(shell->paths, "SHELL", tmp, 1);
	free(lvl_str);
	free(tmp);
}

void	print_banner(void)
{
	printf("\n");
	printf(GREEN_TEXT "███╗   ███╗██╗███╗   ██╗██╗███████╗█");
	printf("█╗  ██╗ █████╗ ██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝█");
	printf("█║  ██║██╔══██╗██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗█");
	printf("██████║███████║██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║█");
	printf("█╔══██║██╔══██║██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║█");
	printf("█║  ██║██║  ██║███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═");
	printf("╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝\n" RESET_TEXT);
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

void	loop(t_shell *new)
{
	char	*line;
	char	*prompt;
	char	*exit;

	while (42)
	{
		set_signals(0);
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (line)
		{
			exit = ft_strtrim(line, " ");
			if (ft_strncmp(exit, "exit", 4) == 0 && (exit[4] == 0
					|| exit[4] == ' '))
				return (free(exit), printf("exit\n"), ft_exit(new, line));
			else
				free(exit);
		}
		if (quotes_counter(line))
			printf("Quotes opened!\n");
		else
			extend(new, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;

	(void)argv;
	if (argc == 1)
	{
		print_banner();
		init_minishell(&new, envp);
		change_shell(new);
		loop(new);
	}
	else
		ft_fprintf(2, "Too many arguments\n");
	return (0);
}
