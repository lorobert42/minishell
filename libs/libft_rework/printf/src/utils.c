/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:42:32 by afavre            #+#    #+#             */
/*   Updated: 2022/11/04 07:01:28 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		res += ft_putchar(str[i]);
		i++;
	}
	return (res);
}

char	*dec2hex(unsigned int input)
{
	char	*hex;
	char	buff[16];
	int		i;
	int		j;
	char	*res;

	hex = "0123456789ABCDEF";
	i = 0;
	j = 0;
	while (input)
	{
		buff[i++] = hex[input % 16];
		input = input / 16;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	while (i > 0)
		res[j++] = buff[--i];
	res[j] = '\0';
	return (res);
}

char	*strlower(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
