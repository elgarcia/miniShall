#include "../Inc/minishell.h"
#include <errno.h>

int	g_pid = 0;

void	change_shell(t_shell *shell)
{
	char	*tmp;
	tmp = ft_strjoin(shell->paths->pwd, "/minishall");
	add_export_node(shell->paths, "SHELL", tmp, 1);
	free(tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;
	char	*line;

	(void)argv;
	if (argc == 1)
	{
		init_minishell(&new);
		fill_init_env_list(new->paths, envp);
		new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
		change_shell(new);
		while (42)
		{
			line = readline(GREEN_TEXT "minishall$ "RESET_TEXT);
		//	printf("line -> %s\n", line); // quitar esto despues;
			if (line == NULL) {
    			fprintf(stderr, "readline error: %s\n", strerror(errno));
    			exit(EXIT_FAILURE);
			}
			if (line[0] != 0)
			{
				if (!ft_strncmp(line, "exit", 5))
					ft_exit(new);
				if (input_parser(line, new) == -1)
					exit(EXIT_FAILURE);
				add_history(line);
				init_pikes(&new);
				exec_process(new, line);
				free_pikes(&new);
			}
			// free_null(&line);
		}
	}
	else
		printf("Too many arguments\n");
	return (0);
}
