/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:42:58 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/08 13:43:00 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (!*line)
			continue ;
		if (*line)
			add_history(line);
		printf("%s\n", line);
		free(line);
	}
	exit(0);
}
