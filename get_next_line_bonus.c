/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:47:31 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/15 16:25:15 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	includes(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_bzero(void *s, unsigned long n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = 0;
}

static int	help(int fd, char **buff, char **return_final, char **remain)
{
	char	*tmp;

	while (read(fd, *buff, BUFFER_SIZE) > 0)
	{
		if (includes(*buff) == -1)
		{
			*return_final = ft_strjoin(*return_final, *buff, 0);
			ft_bzero(*buff, BUFFER_SIZE);
		}
		else
		{
			*remain = ft_substr(*buff, includes(*buff) + 1, ft_strlen(*buff));
			tmp = ft_substr(*buff, 0, includes(*buff) + 1);
			*return_final = ft_strjoin(*return_final, tmp, 1);
			free(*buff);
			return (1);
		}
	}
	if (read(fd, *buff, BUFFER_SIZE) == 0 && **return_final)
	{
		free(*buff);
		return (1);
	}
	free(*buff);
	return (0);
}

static int	manage_remain(char **remain, char **return_final)
{
	char	*tmp;

	if (includes(*remain) == -1)
	{
		*return_final = ft_strjoin(*return_final, *remain, 0);
		ft_bzero(*remain, ft_strlen(*remain));
		free(*remain);
		*remain = 0;
	}
	else
	{
		tmp = ft_substr(*remain, 0, includes(*remain) + 1);
		*return_final = ft_strjoin(*return_final, tmp, 1);
		tmp = *remain;
		*remain = ft_substr(*remain, includes(*remain) + 1, ft_strlen(*remain));
		free(tmp);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*remain;
	char		*return_final;

	return_final = ft_calloc(1, 1);
	if (remain && *remain)
	{
		if (manage_remain(&remain, &return_final))
			return (return_final);
	}
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (buff)
	{
		if (help(fd, &buff, &return_final, &remain))
			return (return_final);
	}
	free(return_final);
	return (0);
}
