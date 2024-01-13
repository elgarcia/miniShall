#include "../Inc/minishell.h"

void	ft_free(char **arg, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

static void	check_word(const char **s1)
{
	if (**s1 == 39)
	{
		while (*(++(*s1)) != 39)
		{
		}
	}
	(*s1)++;
}

int	ft_word_count(const char *s1, char delimiter)
{
	int	counter;
	int	aux;

	aux = 0;
	counter = 0;
	if (!s1)
		return (0);
	while (*s1)
	{
		while (*s1 == delimiter && *s1)
		{
			s1++;
			aux = 1;
		}
		while (*s1 != delimiter && *s1)
		{
			check_word(&s1);
			aux = 2;
		}
		if (aux == 2)
			counter++;
	}
	return (counter);
}