/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <lorobert@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:12:40 by lorobert          #+#    #+#             */
/*   Updated: 2022/08/08 14:53:38 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, void const *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned char const	*s;
	unsigned char		cc;

	d = dest;
	s = src;
	cc = c;
	i = 0;
	while (i < n && s[i] != cc)
	{
		d[i] = s[i];
		i++;
	}
	if (s[i] == cc)
	{
		d[i] = s[i];
		return (d + i + 1);
	}
	return (NULL);
}
