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

void	undo_redirect(t_fds *fds)
{
	size_t	i;

	if (fds->input_fds != NULL)
	{
		i = 0;
		while (i < fds->input_count)
			dup2(fds->input_fds[fds->input_count - 1 - i++], 0);
		free(fds->input_fds);
	}
	if (fds->output_fds != NULL)
	{
		i = 0;
		while (i < fds->output_count)
			dup2(fds->output_fds[fds->output_count - 1 - i++], 1);
		free(fds->output_fds);
	}
	free(fds);
	return ;
}

int	interpret(char *const line)
{
	int		status;
	char	**argv;
	t_token	*tok;
	t_fds	*fds;

	tok = my_tokenizer(line);
	fds = x_calloc(1, sizeof(t_fds));
	if (tok == NULL)
		return (1);
	argv = expansion(tok, fds);
	if (argv == NULL)
		return (free_argv_token(NULL, tok));
	status = exec(argv);
	undo_redirect(fds);
	free_argv_token(argv, tok);
	return (status);
}
