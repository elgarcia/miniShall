#include "../Inc/minishell.h"
#include <errno.h>

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
		init_minishell(&new);
		fill_init_env_list(new->paths, envp);
		new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
		while (42)
		{
			line = readline("minishall$ ");
			if (line == NULL) {
    			fprintf(stderr, "readline error: %s\n", strerror(errno));
    			exit(EXIT_FAILURE);
			}
			if (line[0] != 0)
			{
				if (!ft_strncmp(line, "exit", 4))
					exit(EXIT_SUCCESS);
				if (input_parser(line, new) == -1)
					exit(EXIT_FAILURE);
				add_history(line);
				init_pikes(&new);
				exec_process(new);
				free_pikes(&new);
			}
			free_null(&line);
		}
	}
	else
		printf("Too much arguments\n");
	return (0);
}
