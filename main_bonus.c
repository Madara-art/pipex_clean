/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:25:16 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/24 02:50:05 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "pipex_bonus.h"

void	herdoc_input(char **argv)
{
	int		fd;
	char	*s;

	fd = open("._herdoc_tmp_in_", O_TRUNC | O_CREAT | O_WRONLY, 0666);
	write(1, "heredoc>", 9);
	s = get_next_line(0);
	s[ft_strlen(s) - 1] = 0;
	while (ft_strcmp(s, argv[2]))
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
		write(1, "heredoc>", 9);
		s = get_next_line(0);
		s[ft_strlen(s) - 1] = 0;
	}
	free(s);
	close(fd);
}

void	parent_bloc(int *pipefd1, int fk2)
{
	int	status;

	close(pipefd1[1]);
	close(pipefd1[0]);
	waitpid(fk2, &status, 0);
	while (wait(0) > 0)
		;
	unlink("._herdoc_tmp_in_");
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

void	manage_herdoc(char ***argv, int *argc)
{
	herdoc_input((*argv)++);
	(*argc)--;
	(*argv)[1] = "._herdoc_tmp_in_";
}

int	main(int argc, char *argv[], char *envp[])
{
	int	pipefd[2][2];
	int	fk;
	int	fk2;

	if (!ft_strncmp(argv[1], "here_doc", 9))
		manage_herdoc(&argv, &argc);
	if (pipe(pipefd[0]) == -1)
		exit_fun(2);
	fk = fork();
	if (fk < 0)
		exit_fun(5);
	if (!fk)
		first_child(pipefd[0], argv, envp);
	else
	{
		multi_pipe(argc, argv, envp, pipefd);
		fk2 = fork();
		if (fk2)
			parent_bloc(pipefd[0], fk2);
		else
			last_child(pipefd[0], argv, envp, argc);
	}
	return (0);
}

// 	if (pipe(pipefd1) == -1)
// 		printf("ERROR\n");
// 	// printf("%d %d\n", pipefd[0], pipefd[1]);
// 	arg = ft_split(argv[2], ' ');
// 	fk = fork();
// 	if (fk)
// 	{
// 		wait(0);
// 		close(pipefd1[1]);
// 		fk = fork();
// 		if (fk)
// 		{
// 			close(pipefd[0]);
// 			wait(0);
// 		}
// 		else
// 		{
// 			// fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
// 			// dup2(fd_out, 1);
// 			// dup2(pipefd[0], 0);
// 			// close(pipefd[1]);
// 			close(pipefd1[1]);
// 			read(pipefd[0], &c, 2);
// 			write(1, &c, 2);
// 			free_matrix(arg);
// 			arg = ft_split(argv[3], ' ');
// 			// exit(0);
// 			// while (*arg)
// 			// 	printf("%s\n", *(arg++));
// 			if (execve(check_access(envp, arg[0]), arg, 0) == -1)
// 				printf("ERROR\n");
// 			printf("hello\n");
// 		}
// 	}
// 	else
// 	{
// 		fd_in = open(argv[1], O_RDONLY);
// 		dup2(fd_in, 0);
// 		close(pipefd[0]);
// 		dup2(pipefd[1], 1);
// 		if (execve(check_access(envp, arg[0]), arg, 0) == -1)
// 			printf("ERROR\n");
// 	}
// 	// execve()
// 	// path = check_access(envp, "ls");
// 	// printf("%s\n", path);
// 	// system("leaks a.out");
// 	return (0);
// }

/*Check if cmd exists*/
// path = get_path(envp);
// printf("%s\n", path);
// printf("%d\n", check_access(envp, "aa"));
