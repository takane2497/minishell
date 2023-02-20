/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:07:04 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/20 18:07:05 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	is_builtin(char *command)
{
	if (ft_strncmp(command, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "export", 6) == 0)
		return (1);
	return (0);
}

void	exec_in_builtin(char **argv)
{
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
		exec_pwd(argv);
	if (ft_strncmp(argv[0], "export", 6) == 0)
		exec_export(argv);
	exit(0);
}
