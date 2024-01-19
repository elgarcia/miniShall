#include "../Inc/minishell.h"

void	execute(t_paths *paths, char *line, int argc)
{
	char	**argv;
	int		i;

	i = -1;
	argv = ft_split(line, ' ');
	if (ft_strncmp(line, "cd", 2) == 0)
	{
		ft_cd(paths, "~");
		print_env_list(paths->env_lst);
	}
	else if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(paths);
	else if (ft_strncmp(line, "export", 6) == 0)
		ft_export(paths, argv, 0);
	else if(ft_strncmp(line, "echo", 4) == 0)
		ft_echo(argv, argc);
	if (argv)
	{
		while (argv[++i])
			free(argv[i]);
		free(argv);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;
	char	*line;

	if (argc == 1)
	{
		new = (t_shell *)ft_calloc(1, sizeof(t_shell));
		new->paths = malloc(sizeof(t_paths));
		new->paths->pwd = ft_strdup(getenv("PWD"));
		new->paths->old_pwd = ft_strdup(getenv("OLDPWD"));
		new->paths->home = ft_strdup(getenv("HOME"));
		fill_init_env_list(new->paths, envp);
		new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
		while (42)
		{
			line = readline("minishall$ ");
			if (line[0] != 0)
			{
				// if (input_parser(line, new, envp) == -1)
				//	exit(EXIT_FAILURE);
				// add_history(line);
				execute(new->paths, line, argc);
			}
			if (!ft_strncmp(line, "exit", 4))
				ft_exit(new);
			//printf("%s\n", line);
			printf("\n");
		}
	}
	else
		printf("Too much arguments\n");
	return (0);
}
