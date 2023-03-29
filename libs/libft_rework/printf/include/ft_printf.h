/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:23:20 by afavre            #+#    #+#             */
/*   Updated: 2022/11/04 07:32:54 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

// ft_printf.c
int		ft_printf(const char *str, ...);

// selecteur.c
int		print_data(char type, void *data);

// utils.c
int		ft_putchar(char c);
int		ft_putstr(char *str);
char	*dec2hex(unsigned int input);
char	*strlower(char *str);

// caster1.c
int		cast_char(char c);
int		cast_string(char *str);
int		cast_pointeur(unsigned long long data);
int		cast_decimal(void *data);
int		cast_integer(char *data);

// caster2.c
int		cast_undecimal(char *data);
int		cast_hexa_min(unsigned int data);
int		cast_hexa_maj(unsigned int data);
int		cast_percent(void);

// ft_uitoa.c
char	*ft_uitoa(unsigned int n);

// print_ptr
int		ft_print_ptr(unsigned long long ptr);

#endif
