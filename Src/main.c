#include "../Inc/minishell.h"
#include <errno.h>

void	change_shell(t_shell *shell)
{
	char	*tmp;

	tmp = ft_strjoin(shell->paths->pwd, "/minishall");
	add_export_node(shell->paths, "SHELL", tmp, 1);
	free(tmp);
}

void	extend(t_shell *new, char *line)
{
	if (line == NULL)
	{
		printf("Exit\n");
		ft_exit(new);
	}
	if (line[0] != 0)
	{
		add_to_history(line, ".history");
		if (!ft_strncmp(line, "exit", 5))
			ft_exit(new);
		if (input_parser(line, new) != -1)
		{
			add_history(line);
			init_pikes(&new);
			exec_process(new, line);
			free(line);
			free_pikes(&new);
		}
		else
		{
			add_history(line);
			ft_fprintf(2, "Syntax Error\n");
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
	{
		t_shell	*new;
		char	*line;

		init_minishell(&new);
		fill_init_env_list(new->paths, envp);
		new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
		change_shell(new);
		while (42)
		{
			set_signals(0);
			line = readline(GREEN_TEXT "minishall$ " RESET_TEXT);
			extend(new, line);
		}
		// free_null(&line);
	}
	else		ft_fprintf(2, "Too many arguments\n");
}
