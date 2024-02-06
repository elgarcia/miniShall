#include "../Inc/minishell.h"
#include <errno.h>

int g_exit_status = 0;

void	change_shell(t_shell *shell)
{
	char	*tmp;

	tmp = ft_strjoin(shell->paths->pwd, "/minishall");
	add_export_node(shell->paths, "SHELL", tmp, 1);
	free(tmp);
}

char	*ft_strchrt(char *s, char c, int times)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			i++;
			if (i == times)
				return (s);
		}
		s++;
	}
	return (NULL);
}

char	*get_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp;

	tmp = ft_strchrt(shell->paths->pwd, '/', 3);
	if (!tmp)
		tmp = "/";
	prompt = ft_strjoin("~", tmp);
	return (prompt);
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
		add_to_history(new, line);
		if (!ft_strncmp(line, "exit", 5))
			ft_exit(new);
		if (input_parser(line, new) != -1)
		{
			add_history(line);
			init_pikes(&new);
			exec_process(new, line);
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
		t_shell *new;
		char *line;
		char *prompt;

	(void)argv;
	if (argc == 1)
	{
		init_minishell(&new);
		new->paths->envp = envp;
		fill_init_env_list(new->paths, envp);
		new->paths->export_env_lst = duplicate_lst(new->paths->env_lst);
		change_shell(new);
		while (42)
		{
			set_signals(0);
			prompt = get_prompt(new);
			printf(BLUE_TEXT "%s" RESET_TEXT, prompt);
			line = readline(GREEN_TEXT " minishall > " RESET_TEXT);
			extend(new, line);
			free(prompt);
			free(line);
		}
	}
	else
		ft_fprintf(2, "Too many arguments\n");
}
