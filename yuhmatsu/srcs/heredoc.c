/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:22:16 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/28 18:40:53 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_len_of_heredoc_line(char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			free(get_env_len(line, &i, &len));
		else
		{
			i++;
			len++;
		}
	}
	len++;
	return (len);
}

char	*interpret_line(char *line)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ans;

	if (line == NULL || *line == '\0')
		return (line);
	len = get_len_of_heredoc_line(line);
	ans = x_calloc(len, sizeof(char));
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			j = my_strlcat(ans, get_env_len(line, &i, NULL), len);
		else
			j += concat_char(ans + j, line, &i);
	}
	free(line);
	return (ans);
}

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		pfd[2];
	size_t	len;

	g_all.heredoc_status = CONTINUE;
	signal_in_heredoc();
	len = ft_strlen(delimiter);
	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while (g_all.heredoc_status)
	{
		line = readline("> ");
		if (line == NULL)
			ft_dprintf(STDOUT_FILENO, "\e[A\e[2C");
		line = interpret_line(line);
		if (line == NULL || g_all.heredoc_status == INTERRUPTED || \
			ft_strncmp(line, delimiter, len) == 0)
			break ;
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	free(line);
	close(pfd[1]);
	init_signal();
	return (pfd[0]);
}
