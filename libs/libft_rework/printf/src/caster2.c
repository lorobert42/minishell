/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:15:50 by afavre            #+#    #+#             */
/*   Updated: 2022/11/03 17:14:31 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	cast_undecimal(char *data)
{
	int	res;

	res = 0;
	res = ft_putstr(data);
	free(data);
	return (res);
}

int	cast_hexa_min(unsigned int data)
{
	int		res;
	char	*str;

	if (data == 0)
		res = ft_putstr("0");
	else
	{
		str = dec2hex(data);
		res = ft_putstr(strlower(str));
		free(str);
	}
	return (res);
}

int	cast_hexa_maj(unsigned int data)
{
	int		res;
	char	*str;

	if (data == 0)
		res = ft_putstr("0");
	else
	{
		str = dec2hex(data);
		res = ft_putstr(str);
		free(str);
	}
	return (res);
}

int	cast_percent(void)
{
	int	res;

	res = 0;
	res += ft_putstr("%");
	return (res);
}
