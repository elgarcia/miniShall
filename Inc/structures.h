/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:55:35 by eliagarc          #+#    #+#             */
/*   Updated: 2024/02/06 20:06:53 by eliagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <signal.h>

# define PIPE 0
# define ORD 1
# define IRD 2
# define APND 3
# define HD 4

extern int	g_exit_status;

typedef struct s_split
{
	char	*s;
	char	c;
	char	**strs;
	int		i;
	int		j;
	int		in_quotes;
}			t_split;

typedef struct s_env_lst
{
	char				*name;
	char				*value;
	int					equal;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct s_paths
{
	char				*home;
	char				*pwd;
	char				*old_pwd;
	char				**envp;
	t_env_lst			*env_lst;
	t_env_lst			*export_env_lst;
}						t_paths;

typedef struct s_process
{
	char				*process;
	int					n_process;
	int					type;
	struct s_process	*next;
}						t_process;

typedef struct s_shell
{
	t_process	*lst_process;
	int			n_process;
	int			*pipes;
	int			fd_in;
	int			fd_out;
	int			og_infile;
	int			og_outfile;
	pid_t		*sons;
	char		**exec_args;
	char		**input;
	char		*history_path;
	t_paths		*paths;
}				t_shell;

#endif
