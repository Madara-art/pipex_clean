/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 01:03:18 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/12 21:16:56 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2, int freedom)
{
	char	*p;
	int		len_s1;
	int		len_s2;

	if (!s1)
		return (0);
	if (!s2)
		s2 = ft_calloc(1, 1);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	p = malloc(len_s1 + len_s2 + 1);
	if (p)
	{
		ft_memcpy(p, s1, len_s1);
		ft_memcpy(p + len_s1, s2, len_s2 + 1);
	}
	free(s1);
	if (freedom)
		free(s2);
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	len_s;

	if (len == 0 || !s)
		return (ft_calloc(1, 1));
	len_s = ft_strlen((char *)s);
	if (start >= len_s)
		return ("");
	if (len_s - start < len)
		p = ft_calloc(len_s - start + 1, 1);
	else
		p = ft_calloc(len + 1, 1);
	i = -1;
	if (p)
	{
		while (++i < len && *(char *)(s + start + i))
			p[i] = *(char *)(s + start + i);
	}
	return (p);
}
