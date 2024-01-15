#include "../Inc/minishell.h"

static int	reassign_path(char ***aux2, char *envp)
{
	char	*aux;

	aux = ft_strdup((*aux2)[1]);
	ft_free(*aux2, ft_word_count(envp, '='));
	if (!aux)
		return (-1);
	*aux2 = ft_split(aux, ':');
	if (!*aux2)
		return (-1);
	free(aux);
	return (0);
}

int	assign_path(char ***exec_args, char *command, char **envp)
{
	char	*aux_path;
	char	**aux2;
	int		flag;
	int		i;

	i = -1;
	while (envp[++i])
	{
		aux2 = ft_split(envp[i], '=');
		if (!aux2)
			return (-1);
		if (!ft_strncmp(aux2[0], "PATH", ft_strlen(envp[i])))
		{
			if (reassign_path(&aux2, envp[i]) == -1)
				return (-1);
			flag = search_path(aux2, &aux_path, command, exec_args);
			if (flag == 0 || flag == -1)
				return (ft_free(aux2, ft_word_count(envp[i], ':')), flag);
			break ;
		}
		else
			ft_free(aux2, ft_word_count(envp[i], '='));
	}
	return (ft_free(aux2, ft_word_count(envp[i], ':')), -1);
}

int	check_command(char *command, char ***exec_args)
{
	if (command[0] == '/')
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			(*exec_args)[0] = ft_strdup(command);
			if (!(*exec_args)[0])
				return (ft_free(*exec_args, 1), -1);
			return (0);
		}
		else
			return (ft_printf("%s: command not found\n", command), -1);
	}
	else if (ft_strnstr(command, ".sh", ft_strlen(command)))
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			(*exec_args)[0] = ft_strdup(command);
			if (!(*exec_args)[0])
				return (ft_free(*exec_args, 1), -1);
			return (0);
		}
		else
			return (ft_printf("%s: command not found\n", command), -1);
	}
	return (1);
}

static int	init_cmd(int *aux, char ***cmd_split, char *process)
{
	*cmd_split = ft_split(process, ' ');
	if (!*cmd_split)
		return (-1);
	*aux = ft_word_count(process, ' ') + 1;
	return (0);
}

int	prepare_command(char *process, char ***exec_args, char **envp)
{
	int		aux;
	char	**cmd_split;

	if (init_cmd(&aux, &cmd_split, process) == -1)
		return (-1);
	*exec_args = (char **)ft_calloc(aux, sizeof(char *));
	if (!*exec_args)
		return (ft_free(cmd_split, ft_word_count(process, ' ')), -1);
	aux = check_command(cmd_split[0], exec_args);
	if (aux == 1)
	{
		if (assign_path(exec_args, cmd_split[0], envp) == -1)
			return (ft_free(cmd_split, ft_word_count(process, ' ')), \
				free(*exec_args), -1);
	}
	if (aux == -1 || init_execargs(exec_args, process) == -1)
		return (ft_free(cmd_split, ft_word_count(process, ' ')), -1);
	return (ft_free(cmd_split, ft_word_count(process, ' ')), 0);
}