#include "../Inc/minishell.h"

void	exe_command(t_paths *paths, char **argv, int argc)
{
	if (ft_strncmp(argv[1], "cd", 3) == 0)
		ft_cd(paths, argv[2]);
	else if (ft_strncmp(argv[1], "echo", 5) == 0)
		ft_echo(argv, argc);
	else if (ft_strncmp(argv[1], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(argv[1], "env", 4) == 0)
		ft_env(paths);
	// else if (ft_strncmp(argv[1], "export", 7) == 0)
	//	ft_export(paths, argv);
}

void	execute(t_paths *paths, char *line, int argc)
{
	char	**argv;

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
	{
		argv = ft_split(line, ' ');
		ft_export(paths, argv);
		free(argv);
	}
}

t_env_lst	*duplicate_env_node(const t_env_lst *node)
{
	t_env_lst	*new_node;

	new_node = malloc(sizeof(t_env_lst));
	if (!new_node)
	{
		perror("Error al asignar memoria para el nuevo nodo");
		exit(EXIT_FAILURE);
	}
	new_node->name = strdup(node->name);
	new_node->value = strdup(node->value);
	new_node->next = NULL;
	return (new_node);
}

t_env_lst	*duplicate_lst(const t_env_lst *head)
{
	t_env_lst	*new_head;
	t_env_lst	*current;

	if (!head)
	{
		return (NULL);
	}
	new_head = duplicate_env_node(head);
	current = new_head;
	while (head->next)
	{
		head = head->next;
		current->next = duplicate_env_node(head);
		current = current->next;
	}
	return (new_head);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*new;
	char	*line;

	if (argc == 1)
	{
		new = (t_shell *)ft_calloc(1, sizeof(t_shell));
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
				exit(EXIT_SUCCESS);
			// printf("%s\n", line);
			printf("\n");
		}
	}
	else
		printf("Too much arguments\n");
	return (0);
}
