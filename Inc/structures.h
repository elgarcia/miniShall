#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	struct s_sprocess	*next;
}						t_process;

typedef struct s_shell
{
	t_process	*lst_process;
	char		**input;
	t_paths		*paths;
}				t_shell;

#endif
