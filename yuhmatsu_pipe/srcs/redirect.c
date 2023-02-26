/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:50:26 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/18 18:50:27 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		pfd[2];
	size_t	len;

	len = ft_strlen(delimiter);
	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, len) == 0)
		{
			free(line);
			break ;
		}
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

t_token	*prepare_to_redirect_input(t_token *tmp, int *now_input_fd)
{
	char	*str;

	str = remove_quote(tmp->next->word);
	if (*now_input_fd != 0)
		close(*now_input_fd);
	if (tmp->kind == TK_INPUT)
	{
		*now_input_fd = open(str, O_RDONLY);
		if (*now_input_fd == -1)
		{
			err_msg(str, "No such file or directory");
			free(str);
			return (tmp);
		}
	}
	else
		*now_input_fd = read_heredoc(str);
	free(str);
	tmp = tmp->next->next;
	return (tmp);
}

t_token	*prepare_to_redirect_output(t_token *tmp, int *now_output_fd)
{
	char		*str;

	str = remove_quote(tmp->next->word);
	if (*now_output_fd != 1)
		close(*now_output_fd);
	if (tmp->kind == TK_ADD_OUTPUT)
		*now_output_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, \
					S_IWUSR | S_IRUSR);
	else
		*now_output_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, \
					S_IWUSR | S_IRUSR);
	free(str);
	tmp = tmp->next->next;
	return (tmp);
}

void	redirect(int *now_input_fd, int *now_output_fd)
{
	int	tmp_intput_fd;
	int	tmp_output_fd;

	tmp_intput_fd = dup(0);
	tmp_output_fd = dup(1);
	dup2(*now_input_fd, 0);
	dup2(*now_output_fd, 1);
	*now_input_fd = tmp_intput_fd;
	*now_output_fd = tmp_output_fd;
}
