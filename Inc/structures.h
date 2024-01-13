#ifndef STRUCTURES_H
# define STRUCTURES_H



typedef struct s_process
{
	char				*process;
	struct s_sprocess	*next;
}						t_process;

typedef struct s_shell
{
	t_process	*lst_process;
	char		**input;
}				t_shell;

#endif