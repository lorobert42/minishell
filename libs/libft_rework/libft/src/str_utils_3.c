/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:54:55 by afavre            #+#    #+#             */
/*   Updated: 2022/11/21 11:32:21 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!s)
		return (NULL);
	if (!res)
		return ((void *)0);
	while (i < len)
	{
		res[i] = (f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0' || i == n)
		return (0);
	else
		return (-s2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (*needle == '\0' || needle == NULL)
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *) haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	k;

	str = (char *)s;
	k = (char)c;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == k)
			return (&str[i]);
		i--;
	}
	return (0);
}
