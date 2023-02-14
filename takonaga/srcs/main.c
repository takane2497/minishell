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

int	last_status;

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (!*line)
			continue ;
		if (*line)
			add_history(line);
		last_status = interpret(line);
		free(line);
	}
	exit(last_status);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }
