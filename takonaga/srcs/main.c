/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:11:16 by takonaga          #+#    #+#             */
/*   Updated: 2023/02/09 18:11:19 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	int		status;
	char	*line;

	rl_outstream = stderr;
	status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (!*line)
			continue ;
		if (*line)
			add_history(line);
		status = interpret(line);
		free(line);
	}
	return (0);
	exit(status);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }
