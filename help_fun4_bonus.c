/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun4_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:07:28 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/15 17:08:07 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	childs_bloc_in_multi(int i, int pipefd[2][2], char **argv, char **envp)
{
	char	**arg;

	if (i % 2)
	{
		close(pipefd[1][0]);
		close(pipefd[0][1]);
		dup2(pipefd[0][0], 0);
		dup2(pipefd[1][1], 1);
		arg = ft_split(argv[i], ' ');
		if (execve(check_access(envp, arg[0]), arg, 0) == -1)
			exit_fun(2);
	}
	else
	{
		close(pipefd[1][1]);
		close(pipefd[0][0]);
		dup2(pipefd[1][0], 0);
		dup2(pipefd[0][1], 1);
		arg = ft_split(argv[i], ' ');
		if (execve(check_access(envp, arg[0]), arg, 0) == -1)
			exit_fun(2);
	}
}

void	parent_bloc_in_multi(int *i, int *pipefd2, int *pipefd1)
{
	if (*i % 2)
	{
		close(pipefd1[0]);
		close(pipefd1[1]);
		pipe(pipefd1);
	}
	else
	{
		close(pipefd2[0]);
		close(pipefd2[1]);
		pipe(pipefd2);
	}
	(*i)++;
}

void	multi_pipe(int argc, char **argv, char **envp, int pipefd[2][2])
{
	int	i;
	int	fk;

	i = 3;
	pipe(pipefd[1]);
	while (i < argc - 2)
	{
		fk = fork();
		if (fk < 0)
			exit_fun(5);
		if (!fk)
			childs_bloc_in_multi(i, pipefd, argv, envp);
		else
			parent_bloc_in_multi(&i, pipefd[1], pipefd[0]);
	}
	if (i % 2 == 0)
	{
		pipefd[0][0] = pipefd[1][0];
		pipefd[0][1] = pipefd[1][1];
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}
