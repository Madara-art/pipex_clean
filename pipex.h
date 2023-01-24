/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:54:10 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/24 02:43:44 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

#endif
