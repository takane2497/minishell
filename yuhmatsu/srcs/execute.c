/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:35:00 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/12 09:35:01 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		err_exit(filename, "No such file or directory", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

int	exec(char *argv[])
{
	extern char	**environ;
	const char	*path = argv[0];
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

void	undo_redirect(int *output_fds)
{
	size_t	num_fd;
	size_t	i;

	if (output_fds == NULL)
		return ;
	num_fd = 0;
	i = 0;
	while (output_fds[num_fd] != 0)
		num_fd++;
	while (i < num_fd)
		dup2(output_fds[i], 1);
}

int	interpret(char *const line)
{
	int		status;
	char	**argv;
	t_token	*tok;
	int		*output_fds;

	tok = my_tokenizer(line);
	if (tok == NULL)
		return (1);
	argv = expansion(tok, &output_fds);
	if (argv == NULL)
		return (1);
	status = exec(argv);
	//undo_redirect(output_fds);
	free_argv_token(argv, tok);
	return (status);
}
