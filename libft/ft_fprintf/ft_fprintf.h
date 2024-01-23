/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:24:11 by bautrodr          #+#    #+#             */
/*   Updated: 2024/01/23 23:05:53 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

int		ft_fprintf(int fd, char const *format, ...);
int		ft_putchar(char c, int i, int fd);
int		ft_putnbr(int nb, int i, int fd);
int		print_str(const char *str, int i, int fd);
int		print_hex(unsigned int x, int len, int c, int fd);
int		print_address(void *ptr, int i, int fd);
int		unsigned_int(unsigned int nb, int i, int fd);
int		check_format(va_list args, const char *format, int i, int j, int fd);

#endif
