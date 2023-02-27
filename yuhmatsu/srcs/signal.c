/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:43:05 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/27 20:22:00 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	continue_new_line(int sig)
{
	sig++;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_all.last_status = 1;
}

void	init_signal(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		fatal_error("error in signal handling");
	if (signal(SIGINT, continue_new_line) == SIG_ERR)
		fatal_error("error in signal handling");
	rl_event_hook = NULL;
}

int	signal_checker_in_heredoc(void)
{
	if (g_all.heredoc_status == INTERRUPTED)
		rl_done = 1;
	return (0);
}

void	heredoc_interrupted(int sig)
{
	sig++;
	g_all.heredoc_status = INTERRUPTED;
	g_all.last_status = 1;
}

void	signal_in_heredoc(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		fatal_error("error in signal handling");
	if (signal(SIGINT, heredoc_interrupted) == SIG_ERR)
		fatal_error("error in signal handling");
	rl_event_hook = signal_checker_in_heredoc;
}
