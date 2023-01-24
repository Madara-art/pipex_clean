/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:13:05 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/24 02:43:22 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst || src)
	{
		i = -1;
		while (++i < n)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	return (dst);
}

size_t	ft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

void	exit_fun(int status)
{
	perror("ERROR");
	exit(status);
}

void	first_child(int *pipefd1, char **argv, char **envp)
{
	int		fd_in;
	char	**arg;

	close(pipefd1[0]);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		exit_fun(1);
	dup2(fd_in, 0);
	dup2(pipefd1[1], 1);
	close(pipefd1[1]);
	arg = ft_split(argv[2], ' ');
	if (execve(check_access(envp, arg[0]), arg, 0) == -1)
		exit_fun(127);
}

void	last_child(int *pipefd1, char **argv, char **envp, int argc)
{
	int		fd_out;
	char	**arg;

	close(pipefd1[1]);
	dup2(pipefd1[0], 0);
	fd_out = open(argv[argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (fd_out < 0)
		exit_fun(1);
	arg = ft_split(argv[argc - 2], ' ');
	dup2(fd_out, 1);
	if (execve(check_access(envp, arg[0]), arg, 0) == -1)
		exit_fun(127);
}
