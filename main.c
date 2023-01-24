/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:25:16 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/24 02:44:22 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_bloc(int pipefd1[2], int fk1, int fk2)
{
	int	status;

	close(pipefd1[0]);
	close(pipefd1[1]);
	waitpid(fk1, &fk1, 0);
	waitpid(fk2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

void	is_arg_valid(int argc)
{
	if (argc != 5)
	{
		write(1, "invalid number of arguments!\n", 29);
		exit(1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	pipefd1[2];
	int	fk1;
	int	fk2;

	is_arg_valid(argc);
	if (pipe(pipefd1) == -1)
		exit_fun(2);
	fk1 = fork();
	if (fk1 < 0)
		exit_fun(5);
	if (!fk1)
		first_child(pipefd1, argv, envp);
	else
	{
		fk2 = fork();
		if (fk2 < 0)
			exit_fun(5);
		if (fk2)
			parent_bloc(pipefd1, fk1, fk2);
		else
			last_child(pipefd1, argv, envp, argc);
	}
	return (0);
}
