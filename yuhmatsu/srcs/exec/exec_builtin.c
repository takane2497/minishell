/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:07:04 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/22 02:08:46 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	is_builtin(char *command)
{
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	exec_in_builtin(char **argv, int now_input_fd, int now_output_fd)
{
	int	status;

	if (now_input_fd != -1)
		redirect(&now_input_fd, &now_output_fd);
	if (ft_strcmp(argv[0], "pwd") == 0)
		status = exec_pwd(argv);
	if (ft_strcmp(argv[0], "export") == 0)
		status = (exec_export(argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		status = (exec_echo(argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		status = (exec_unset(argv));
	if (ft_strcmp(argv[0], "env") == 0)
		status = (exec_env());
	if (ft_strcmp(argv[0], "cd") == 0)
		status = (exec_cd(argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		status = (exec_exit(argv));
	undo_redirect(now_input_fd, now_output_fd);
	return (status);
}
