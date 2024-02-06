#include "../Inc/minishell.h"

int	is_builting(t_process *prc)
{
	char 	**aux;
	int		len;

	len = ft_word_count(prc->process, ' ');
	aux = ft_split(prc->process, ' ');
	if (!ft_strncmp(aux[0], "export", 7))
		return (ft_free(aux, len), 1);
	else if (!ft_strncmp(aux[0], "unset", 6))
		return (ft_free(aux, len), 1);
	else if (!ft_strncmp(aux[0], "env", 4))
		return (ft_free(aux, len), 1);
	else if (!ft_strncmp(aux[0], "history", 8))
		return (ft_free(aux, len), 1);
	else if (!ft_strncmp(aux[0], "echo", 5))
		return (ft_free(aux, len), 1);
	else if (!ft_strncmp(aux[0], "cd", 3))
		return (ft_free(aux, len), 1);
	else if (!ft_strncmp(aux[0], "pwd", 4))
		return (ft_free(aux, len), 1);
	return (ft_free(aux, len), 0);
}

void	init_pipex(t_shell *all, t_process *prc, pid_t *pid)
{
	if (prc->n_process == 0 && !is_builting(prc))
		open_file(prc->process, &all->fd_in);
	if (prc->next || (!ft_strncmp(prc->process, "cat", 4) && ft_strlen(prc->process) != 4))
	{
		if (pipe(all->pipes) == -1)
		{
			perror("Pipe failed!");
			exit(EXIT_FAILURE);
		}
	}
	if (prc->next || !is_builting(prc))
	{
		// int hola = 1;
		*pid = fork();
		/* printf("%i\n", *pid);
		while (hola == 1)
		{} */
		if (*pid < 0)
		{
			perror("Fork failed!");
			exit(EXIT_FAILURE);
		}
	}
}

int	open_file(char *file, int *fd)
{
	char 	*aux;

	aux = get_ifile(file, 1);
	if (!aux)
		return (0);
	if (access(aux, F_OK | R_OK) == -1)
		return (free(aux), -1);
	*fd = open(aux, O_RDONLY);
	if (*fd == -1)
	{
		perror("Failed to open output file");
		free(aux);
		return (-1);//error 1(?)
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
		return (-1);
	free(aux);
	close(*fd);
	return (0);
}
