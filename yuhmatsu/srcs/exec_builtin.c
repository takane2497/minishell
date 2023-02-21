/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:07:04 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/21 15:25:28 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	is_builtin(char *command)
{
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	return (0);
}

int	exec_in_builtin(char **argv)
{
	printf("builtin\n");
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (exec_pwd(argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (exec_export(argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (exec_echo(argv));
	return (1);
}
