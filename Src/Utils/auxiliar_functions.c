/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:42:06 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/09 20:45:42 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minishell.h"

int	is_builting(t_process *prc)
{
	char	**aux;
	int		len;

	len = ft_word_count(prc->process, ' ');
	aux = ft_split(prc->process, ' ');
	if (!aux || !aux[0])
		return (0);
	if (!ft_strncmp(aux[0], "export", 7))
		return (ft_free(&aux, len), 1);
	else if (!ft_strncmp(aux[0], "unset", 6))
		return (ft_free(&aux, len), 1);
	else if (!ft_strncmp(aux[0], "env", 4))
		return (ft_free(&aux, len), 1);
	else if (!ft_strncmp(aux[0], "history", 8))
		return (ft_free(&aux, len), 1);
	else if (!ft_strncmp(aux[0], "echo", 6))
		return (ft_free(&aux, len), 1);
	else if (!ft_strncmp(aux[0], "cd", 3))
		return (ft_free(&aux, len), 1);
	else if (!ft_strncmp(aux[0], "pwd", 4))
		return (ft_free(&aux, len), 1);
	else if (!ft_strncmp(aux[0], "exit", 5))
		return (ft_free(&aux, len), 1);
	return (ft_free(&aux, len), 0);
}

int	is_rdp(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	else if (!ft_strcmp(str, "||"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (1);
	else if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, ">"))
		return (1);
	else if (ft_strnstr(str, ">>>", ft_strlen(str)))
		return (1);
	else if (ft_strnstr(str, "<<<", ft_strlen(str)))
		return (1);
	else if (ft_strnstr(str, "> <", ft_strlen(str)))
		return (1);
	else if (ft_strnstr(str, "< >", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_rd(int inout)
{
	if (inout < 0 || inout > 4)
		return (0);
	return (1);
}

void	close_pipes(t_shell *all)
{
	if (dup2(all->og_infile, STDIN_FILENO) == -1)
        exit_error("dup2 failed");
	if (dup2(all->og_outfile, STDOUT_FILENO) == -1)
        exit_error("dup2 failed");
	all->fd_in = -1;
	all->fd_out = -1;
}

void	close_fds(t_shell *all)
{
	if (close(all->fd_out) == -1)
        exit_error("close failed 2");
	if (close(all->fd_in) == -1)
        exit_error("close failed 3");
}
