/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:54:13 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/12 21:08:54 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	nbr_of_words(char *str, char c)
{
	int	i;
	int	nb_wrd;
	int	t_stat;

	i = 0;
	nb_wrd = 0;
	t_stat = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			i++;
			t_stat = 1;
		}
		if (t_stat)
			nb_wrd++;
		t_stat = 0;
	}
	return (nb_wrd);
}

static void	free_alloc(char **p, int j)
{
	while (j--)
	{
		free(p[j]);
	}
	free(p);
}

static char	**fill_the_cringe(char *s, char **p, char c)
{
	int	i;
	int	start;
	int	j;
	int	k;

	i = 0;
	j = -1;
	while (s[i] && ++j < nbr_of_words((char *)s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		p[j] = ft_calloc(i - start + 1, 1);
		if (!p[j])
		{
			free_alloc(p, j);
			return (0);
		}
		k = 0;
		while (start < i)
			p[j][k++] = s[start++];
	}
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;

	if (!s)
		return (0);
	p = ft_calloc(nbr_of_words((char *)s, c) + 1, sizeof(char *));
	if (p)
	{
		p = fill_the_cringe((char *)s, p, c);
	}
	return (p);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			tot;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	p = malloc(size * count);
	if (p)
	{
		tot = count * size;
		while (tot--)
			*(p + tot) = 0;
	}
	return (p);
}
