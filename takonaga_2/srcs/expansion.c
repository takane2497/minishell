/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:35:59 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/12 13:36:03 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	concat_in_singl_quote(char *str, char *word, size_t *i)
{
	size_t	j;

	j = 0;
	*i += 1;
	while (word[*i] != '\'')
	{
		str[j] = word[*i];
		*i += 1;
		j += 1;
	}
	*i += 1;
	return (j);
}

size_t	concat_in_double_quote(char *str, char *word, size_t *i, size_t len)
{
	size_t	j;

	j = 0;
	*i += 1;
	while (word[*i] != '\"')
	{
		if (word[*i] == '$')
			j = my_strlcat(str, get_env_len(word, i, NULL), len);
		else
		{
			str[j] = word[*i];
			*i += 1;
			j++;
		}
	}
	*i += 1;
	return (j);
}

size_t	concat_char(char *str, char *word, size_t *i)
{
	*str = word[*i];
	*i += 1;
	return (1);
}

char	*remove_quote(char *word)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	len = get_len_word(word);
	str = x_malloc(len * sizeof(char));
	*str = '\0';
	while (word[i] != '\0')
	{
		if (word[i] == '$')
			j = my_strlcat(str, get_env_len(word, &i, NULL), len);
		else if (word[i] == '\'')
			j += concat_in_singl_quote(str + j, word, &i);
		else if (word[i] == '\"')
			j += concat_in_double_quote(str + j, word, &i, len);
		else
			j += concat_char(str + j, word, &i);
	}
	str[j] = '\0';
	return (str);
}

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

char	**expansion(t_token *tok, int *now_input_fd, int *now_output_fd)
{
	char	**argv;
	size_t	size;
	size_t	i;
	t_token	*tmp;

	size = token_size(tok);
	if (size == 0)
		return (NULL);
	argv = x_calloc((size + 1), sizeof(char *));
	tmp = tok->next;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->kind == TK_INPUT || tmp->kind == TK_DELIMITER)
		{
			tmp = prepare_to_redirect_input(tmp, now_input_fd);
			if (*now_input_fd == -1)
				break ;
		}
		else if (tmp->kind == TK_OUTPUT || tmp->kind == TK_ADD_OUTPUT)
			tmp = prepare_to_redirect_output(tmp, now_output_fd);
		else if (tmp->kind == TK_WORD)
		{
			argv[i++] = remove_quote(tmp->word);
			tmp = tmp->next;
		}
	}
	if (*now_input_fd != -1)
		redirect(now_input_fd, now_output_fd);
	argv[i] = NULL;
	return (argv);
}
