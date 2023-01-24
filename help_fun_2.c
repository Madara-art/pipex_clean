/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouabda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:13:29 by hbouabda          #+#    #+#             */
/*   Updated: 2023/01/12 21:08:59 by hbouabda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp)
{
	int		i;
	char	*path;

	path = "";
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = ft_strjoin_libft("", envp[i] + 5);
		i++;
	}
	return (path);
}

void	free_matrix(char **m)
{
	int	i;

	i = -1;
	while (m[++i])
		free(m[i]);
	free(m);
}

char	*check_access(char **envp, char *cmd)
{
	char	*path;
	char	**splited_path;
	int		i;
	char	*s;

	path = get_path(envp);
	splited_path = ft_split(path, ':');
	i = -1;
	free(path);
	while (splited_path[++i])
	{
		s = splited_path[i];
		splited_path[i] = ft_strjoin_libft(s, "/");
		free(s);
		s = ft_strjoin_libft(splited_path[i], cmd);
		if (!access(s, X_OK))
			return (free_matrix(splited_path), s);
		free(s);
	}
	return (free_matrix(splited_path), cmd);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strjoin_libft(char const *s1, char const *s2)
{
	char	*p;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	p = malloc(len_s1 + len_s2 + 1);
	if (p)
	{
		ft_memcpy(p, s1, len_s1);
		ft_memcpy(p + len_s1, s2, len_s2 + 1);
	}
	return (p);
}
