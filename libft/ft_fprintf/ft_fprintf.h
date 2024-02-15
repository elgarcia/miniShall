/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:24:11 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/15 10:14:43 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fprintf
{
	int	i;
	int	j;
}		t_fprintf;

int		ft_fprintf(int fd, char const *format, ...);
int		ft_putchar(char c, int i, int fd);
int		ft_putnbr(int nb, int i, int fd);
int		print_str(const char *str, int i, int fd);
int		print_hex(unsigned int x, int len, int c, int fd);
int		print_address(void *ptr, int i, int fd);
int		unsigned_int(unsigned int nb, int i, int fd);
int		check_format(va_list args, const char *format, t_fprintf fprintf,
			int fd);

#endif
