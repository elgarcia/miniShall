#ifndef STRUCTURES_H
# define STRUCTURES_H

# define PIPE 0
# define ORD 1
# define IRD 2
# define APND 3
# define HD 4

typedef struct s_env_lst
{
	char				*name;
	char				*value;
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
	int					type;
	struct s_process	*next;
}						t_process;

typedef struct s_shell
{
	t_process	*lst_process;
	int			n_process;
	char		**exec_args;
	char		**input;
	t_paths		*paths;
}				t_shell;

#endif