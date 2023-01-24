/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:23:42 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/15 17:09:09 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	**ft_split(char const *s, char c);
size_t	ft_strlen(char *str);
char	*ft_strjoin_libft(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(char *s1, char *s2, int n);
char	*get_path(char **envp);
void	*ft_calloc(size_t count, size_t size);
char	*check_access(char **envp, char *cmd);
void	free_matrix(char **m);
void	exit_fun(int status);
void	first_child(int *pipefd1, char **argv, char **envp);
void	last_child(int *pipefd1, char **argv, char **envp, int argc);
void	childs_bloc_in_multi(int i, int pipefd[2][2], char **argv, char **envp);
void	parent_bloc_in_multi(int *i, int *pipefd2, int *pipefd1);
void	multi_pipe(int argc, char **argv, char **envp, int pipefd[2][2]);
int		ft_strcmp(char *s1, char *s2);

#endif
