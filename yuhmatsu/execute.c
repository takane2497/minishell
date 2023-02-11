/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:16:56 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/09 14:16:56 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excecute_process(char *line)
{
	extern char	**environ;
	char		*argv[3];
	pid_t		pid;
	int			status;

	argv[0] = line;
	argv[1] = "/Users/yuhmatsu/42/minishell/yuhmatsu";
	argv[2] = NULL;
	pid = fork();
	if (pid < 0)
	{
		free(line);
		exit(1);
	}
	else if (pid == 0)
	{
		execve(line, argv, environ);
		free(line);
		exit(1);
	}
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	free(line);
	exit(1);
}
