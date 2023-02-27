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

void	exec_in_nonbuiltin(char **argv, int now_input_fd, \
								int now_output_fd, const char *path)
{
	if (now_input_fd != -1)
		redirect(&now_input_fd, &now_output_fd);
	execve(path, argv, g_all.environ);
	undo_redirect(now_input_fd, now_output_fd);
}

// is_builtin(argv[0]) && fds->num_pipe == 0 の場合に内蔵コマンドを実行する関数
int	exec_builtin(char *argv[], t_fds *fds)
{
	return (exec_in_builtin(argv, fds->now_input_fd, fds->now_output_fd));
}

// パイプを使用している場合の子プロセスを生成してコマンドを実行する関数
void	exec_child(char *argv[], t_fds *fds, int pfd[2], size_t *i)
{
	const char	*path = argv[0];

	if (fds->old_pipe_input_fd != 0)
	{
		dup2(fds->old_pipe_input_fd, 0);
		close(fds->old_pipe_input_fd);
	}
	if (*i < fds->num_pipe)
	{
		dup2(pfd[1], 1);
		close(pfd[1]);
		close(pfd[0]);
	}
	if (is_builtin(argv[0]))
		exit(exec_builtin(argv, fds));
	if (ft_strchr(path, '/') == NULL)
		path = search_path(path);
	validate_access(path, argv[0]);
	exec_in_nonbuiltin(argv, fds->now_input_fd, fds->now_output_fd, path);
	fatal_error("execve");
}

// パイプを使用している場合に親プロセスを更新する関数
void	exec_parent(t_fds *fds, int pfd[2], size_t *i)
{
	if (fds->old_pipe_input_fd != 0)
		close(fds->old_pipe_input_fd);
	if (*i < fds->num_pipe)
	{
		fds->old_pipe_input_fd = pfd[0];
		close(pfd[1]);
	}
	*i += 1;
}

// コマンドを実行するメインの関数
int	exec(char *argv[], size_t *i, t_fds *fds)
{
	pid_t	pid;
	int		pfd[2];

	if (is_builtin(argv[0]) && fds->num_pipe == 0)
		return (exec_builtin(argv, fds));
	if (*i < fds->num_pipe && pipe(pfd) < 0)
		fatal_error("pipe");
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		exec_child(argv, fds, pfd, i);
	else
		exec_parent(fds, pfd, i);
	return (0);
}
