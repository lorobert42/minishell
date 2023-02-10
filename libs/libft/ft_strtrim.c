/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:34:27 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/13 13:39:51 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_res_len(char const *s, char const *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	if (len)
		i = len - 1;
	while (ft_is_in_set(s[i], set) && len)
	{
		len--;
		i--;
	}
	i = 0;
	while (ft_is_in_set(s[i], set) && s[i] && len)
	{
		len--;
		i++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	len = ft_res_len(s1, set);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (ft_is_in_set(s1[i], set) && s1[i])
		i++;
	j = 0;
	while (j < len && s1[i])
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
