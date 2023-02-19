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
		err_exit(filename, "command not found", 127);
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

void	undo_redirect(int now_input_fd, int now_output_fd)
{
	close(0);
	close(1);
	dup2(now_input_fd, 0);
	dup2(now_output_fd, 1);
	close(now_input_fd);
	close(now_output_fd);
	return ;
}

int	interpret(char *const line)
{
	char	**argv;
	t_token	*tok;
	int		now_input_fd;
	int		now_output_fd;
	t_token	*tok_head;

	now_input_fd = 0;
	now_output_fd = 1;
	tok_head = new_token(NULL);
	tok = my_tokenizer(line, tok_head);
	if (tok == NULL)
		return (ERROR_TOKENIZE);
	argv = expansion(tok, &now_input_fd, &now_output_fd);
	if (argv == NULL || now_input_fd == -1)
	{
		return (free_argv_token(argv, tok) + 1);
	}
	g_last_status = exec(argv);
	undo_redirect(now_input_fd, now_output_fd);
	free_argv_token(argv, tok);
	return (g_last_status);
}
