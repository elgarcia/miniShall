#include "../Inc/minishell.h"

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

	(void)argv;
	if (argc == 1)
	{
		new = (t_shell *)ft_calloc(1, sizeof(t_shell));
		new->n_process = 0;
		new->input = NULL;
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
				if (!ft_strncmp(line, "exit", 4))
					exit(EXIT_SUCCESS);
				if (input_parser(line, new) == -1)
					exit(EXIT_FAILURE);
				add_history(line);
				new->sons = (pid_t *)ft_calloc(new->n_process, sizeof(pid_t));
				new->pipes = (int **)ft_calloc(new->n_process, sizeof(int *));
				exec_process(new, envp);
			}
		}
	}
	else
		printf("Too much arguments\n");
	return (0);
}
