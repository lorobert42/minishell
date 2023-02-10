/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:33:08 by lorobert          #+#    #+#             */
/*   Updated: 2022/08/12 09:53:18 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t	i;
	size_t	dlen;

	dlen = 0;
	while (dest[dlen] && dlen < size)
		dlen++;
	if (size == 0 || dest[dlen] != '\0')
		return (dlen + ft_strlen(src));
	i = 0;
	while (dlen + i < size - 1 && src[i])
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + ft_strlen(src));
}
