/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:35:00 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/26 10:49:23 by yuhmatsu         ###   ########.fr       */
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

void	exec_in_nonbuiltin(char **argv, int now_input_fd, int now_output_fd, const char *path)
{
	if (now_input_fd != -1)
		redirect(&now_input_fd, &now_output_fd);
	execve(path, argv, g_all.environ);
	undo_redirect(now_input_fd, now_output_fd);
}

int	exec(char *argv[], size_t *i, size_t num_pipe, int now_input_fd, int now_output_fd, int *old_pipe_input_fd)
{
	const char	*path = argv[0];
	pid_t		pid;
	int			pfd[2];

	if (is_builtin(argv[0]) && num_pipe == 0)
		return (exec_in_builtin(argv, now_input_fd, now_output_fd));
	if (*i < num_pipe && pipe(pfd) < 0)
		fatal_error("pipe");
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		if (*old_pipe_input_fd != 0)
		{
			dup2(*old_pipe_input_fd, 0);
			close(*old_pipe_input_fd);
		}
		if (*i < num_pipe)
		{
			dup2(pfd[1], 1);
			close(pfd[1]);
			close(pfd[0]);
		}
		if (is_builtin(argv[0]))
			exit(exec_in_builtin(argv, now_input_fd, now_output_fd));
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		exec_in_nonbuiltin(argv, now_input_fd, now_output_fd, path);
		fatal_error("execve");
	}
	else
	{
		if (*old_pipe_input_fd != 0)
			close(*old_pipe_input_fd);
		if (*i < num_pipe)
		{
			*old_pipe_input_fd = pfd[0];
			close(pfd[1]);
		}
		*i += 1;
		return (0);
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
	pid_t	pid;

//	printf("now:%ld\n", i);
	while (i)
	{
		pid = wait(&wstatus);
		if (pid == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		i--;
	}
	return (wstatus);
}

int	interpret(char *const line)
{
	char	**argv;
	t_token	*tok;
	int		now_input_fd;
	int		now_output_fd;
	int 	old_pipe_input_fd;
	t_token	*tok_head;
	size_t	num_pipe;
	size_t	i;

	i = 0;
	tok_head = new_token(NULL);
	tok = my_tokenizer(line, tok_head);
	if (tok == NULL)
		return (ERROR_TOKENIZE);
	num_pipe = count_pipe(tok_head);
	old_pipe_input_fd = 0;
	while (tok != NULL)
	{
		now_input_fd = 0;
		now_output_fd = 1;
		argv = expansion(&tok, &now_input_fd, &now_output_fd);
		if (argv == NULL || now_input_fd == -1)
			return (free_argv_token(argv, tok_head) + 1);
		g_all.last_status = exec(argv, &i, num_pipe, now_input_fd, now_output_fd, &old_pipe_input_fd);
//		undo_redirect(now_input_fd, now_output_fd);
		// free(argv);
	}
	if (0 < i)
		g_all.last_status = all_wait(i);
	free_argv_token(argv, tok_head);
	return (g_all.last_status);
}



// while ()
// {
// 	argv = expansion(&tok, &now_input_fd, &now_output_fd);
// 	if (argv == NULL || now_input_fd == -1)
// 	{
// 		return (free_argv_token(argv, tok) + 1);
// 	}
// 	g_all.last_status = exec(argv);
// 	free(argv);
// }