#include "../../Inc/minishell.h"

void    exit_error(char *str)
{
    ft_fprintf(2, RED_TEXT"%s\n"RESET_TEXT, str);
    exit(-1);
}
