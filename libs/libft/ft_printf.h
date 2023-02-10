/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:13:44 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/26 11:09:53 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdbool.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_conversion {
	const char	*format;
	va_list		args;
	bool		minus;
	bool		zero;
	bool		point;
	bool		hash;
	bool		space;
	bool		plus;
	int			width;
	int			precision;
	char		specifier;
}	t_conversion;

int		ft_printf(const char *format, ...);
int		ft_printf_char(t_conversion *c);
int		ft_printf_int(t_conversion *c);
int		ft_printf_ptr(t_conversion *c);
int		ft_printf_string(t_conversion *c);
int		ft_printf_uint(t_conversion *c);
int		ft_printf_hex(t_conversion *c, int is_upp);
char	*ft_itoa_unsigned(unsigned int n);
char	*ft_itoa_hex(unsigned int n, int is_upp);
char	*ft_itoa_hex_long(unsigned long int n, int is_upp);

#endif
