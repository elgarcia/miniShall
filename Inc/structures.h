/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:55:35 by eliagarc          #+#    #+#             */
/*   Updated: 2024/05/10 13:28:15 by tuta             ###   ########.fr       */
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

extern int				g_exit_status;

typedef struct s_shell t_shell;

typedef struct s_env_lst
{
	char				*name;
	char				*value;
	int					equal;
	struct s_env_lst	*next;
}						t_env_lst;

typedef struct s_paths
{
	char				**envp;
	t_env_lst			*env_lst;
	t_env_lst			*export_env_lst;
    t_shell             *shell;
}						t_paths;

typedef struct s_redir
{
	int					type;
	int					pos;
	struct s_redir		*next;
}						t_redir;

typedef struct s_process
{
	char				*process;
	int					n_process;
	int					n_redis;
	t_redir				*rd;
	struct s_process	*next;
}						t_process;

typedef struct s_shell
{
	t_process			*lst_process;
	int					n_process;
	int					*pipes;
	int					fd_in;
	int					fd_out;
	int					og_infile;
	int					og_outfile;
	pid_t				*sons;
	char				**word_split;
	char				**exec_args;
	char				**input;
	char				*history_path;
	int					exit_status;
	t_paths				*paths;
}						t_shell;

#endif
