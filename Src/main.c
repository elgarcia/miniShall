/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:51:37 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/13 16:28:28 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structures.h"

void	change_shell(t_shell *shell)
{
	char	*tmp;
	char	tmp2[PATH_MAX];
	int		lvl;
	char	*lvl_str;

	tmp = ft_strjoin(getcwd(tmp2, PATH_MAX), "/minishell");
	lvl_str = get_env(shell, "SHLVL", shell->paths->env_lst);
	lvl = ft_atoi(lvl_str) + 1;
	if (!lvl || lvl < 0 || lvl >= 1000)
	{
		if (lvl >= 1000)
		{
			printf("warning: shell level (%d) too high, resetting to 1\n", lvl);
			lvl = 1;
		}
		else
			lvl = 0;
	}
	free(lvl_str);
	lvl_str = ft_itoa(lvl);
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

	if (line[0] != 0)
	{
		if (!check_opened_quotes(line, 2, 2))
			return ;
		add_to_history(new, line);
		add_history(line);
		new_line = expansor(new, line, -1);
		if (!new_line || !*new_line || new_line[0] == '\n')
			return ;
		if (input_parser(new_line, new, 0) != -1)
		{
			add_history(line);
			init_pikes(&new);
			free(new_line);
			exec_process(new, 0, 0, 0);
			free_pikes(&new);
		}
		else
			free(new_line);
	}
}

void	loop(t_shell *new, char *line, char *prompt)
{
	while (42)
	{
		prompt = get_prompt();
		set_signals(0);
		line = readline(prompt);
		if (line == NULL)
		{
			free(prompt);
			clear_everything(new, 0);
			exit(0);
		}
		signal(SIGINT, SIG_IGN);
		if (g_exit_status == 1)
			new->exit_status = g_exit_status;
		free(prompt);
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
		loop(new, NULL, NULL);
	}
	else
		ft_fprintf(2, "Too many arguments\n");
	return (0);
}
