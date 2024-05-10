/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:12:49 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/15 13:29:17 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_proc(t_process *lst)
{
	if (!lst)
		return ;
	else
	{
		free(lst->process);
		free(lst);
	}
}

void	ft_lstclear_pro(t_process **lst)
{
	t_process	*current;
	t_process	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone_proc(current);
		current = next;
	}
	*lst = NULL;
}
