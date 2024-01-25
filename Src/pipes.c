#include "../Inc/minishell.h"

void	init_pipex(t_shell *all, t_process *prc, pid_t *pid)
{
	if (prc->n_process == 0)
		open_file(prc->process, &all->fd_in);
	if (prc->next)
	{
		if (pipe(all->pipes) == -1)
		{
			perror("Pipe failed!");
			exit(EXIT_FAILURE);
		}
	}
	if (pid)
	{
		*pid = fork();
		if (*pid < 0)
		{
			perror("Fork failed!");
			exit(EXIT_FAILURE);
		}
	}
}

int	open_file(char *file, int *fd)
{
	char *aux;
	
	aux = get_ifile(file);
	if (!aux)
		return (0);
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
