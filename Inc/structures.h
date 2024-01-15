#ifndef STRUCTURES_H
# define STRUCTURES_H

# define PIPE 0
# define ORD 1
# define IRD 2
# define APND 3
# define HD 4

typedef struct s_process
{
	char				*process;
	int					type;
	struct s_process	*next;
}						t_process;

typedef struct s_shell
{
	t_process	*lst_process;
	char		**input;
}				t_shell;

#endif