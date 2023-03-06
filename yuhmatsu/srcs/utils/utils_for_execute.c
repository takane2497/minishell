/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:29:08 by takonaga          #+#    #+#             */
/*   Updated: 2023/03/06 23:01:56 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_pipe(t_token *tok)
{
	size_t	num_pipe;

	num_pipe = 0;
	while (tok != NULL)
	{
		if (tok->kind == TK_PIPE)
			num_pipe++;
		tok = tok->next;
	}
	return (num_pipe);
}

int	all_wait(size_t	i)
{
	int		wstatus;
	int		last_wstatus;
	pid_t	pid;

	while (i)
	{
		pid = wait(&wstatus);
		if (pid == g_all.last_pid)
		{
			if (WIFSIGNALED(wstatus))
				last_wstatus = 128 + WTERMSIG(wstatus);
			else
				last_wstatus = WEXITSTATUS(wstatus);
		}
		if (pid == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		i--;
	}
	return (last_wstatus);
}

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH");
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PASS_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (x_strdup(path));
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}
