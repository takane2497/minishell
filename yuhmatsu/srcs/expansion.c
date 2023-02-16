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
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

t_token	*prepare_to_redirect_input(t_token *tmp, t_fds *fds)
{
	char	*str;

	str = remove_quote(tmp->next->word);
	if (tmp->kind == TK_INPUT)
	{
		fds->input_fds[fds->input_index] = open(str, O_RDONLY);
		//error処理しないとまずい
	}
	else
		fds->input_fds[fds->input_index] = read_heredoc(str);
	free(str);
	tmp = tmp->next->next;
	return (tmp);
}

t_token	*redirect_output(t_token *tmp, t_fds *fds)
{
	char		*str;
	int			tmp_fd;

	str = remove_quote(tmp->next->word);
	if (tmp->kind == TK_ADD_OUTPUT)
		tmp_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, \
					S_IWUSR | S_IRUSR);
	else
		tmp_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, \
					S_IWUSR | S_IRUSR);
	free(str);
	fds->output_fds[fds->output_index] = dup(1);
	fds->output_index++;
	dup2(tmp_fd, 1);
	close(tmp_fd);
	tmp = tmp->next->next;
	return (tmp);
}

void	redirect_input(t_fds *fds)
{
	size_t	i;
	size_t	tmp_fd;

	i = 0;
	while (i < fds->input_count)
	{
		tmp_fd = fds->input_fds[i];
		fds->input_fds[i] = dup(0);
		i++;
		dup2(tmp_fd, 0);
		if (i != fds->input_count)
			close(tmp_fd);
	}
}

char	**expansion(t_token *tok, t_fds *fds)
{
	char	**argv;
	size_t	size;
	size_t	i;
	t_token	*tmp;

	size = token_size(tok, fds);
	if (size == 0)
		return (NULL);
	argv = x_calloc((size + 1), sizeof(char *));
	tmp = tok->next;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->kind == TK_INPUT || tmp->kind == TK_DLIMITER)
			tmp = prepare_to_redirect_input(tmp, fds);
		else if (tmp->kind == TK_OUTPUT || tmp->kind == TK_ADD_OUTPUT)
			tmp = redirect_output(tmp, fds);
		else if (tmp->kind == TK_WORD)
		{
			argv[i++] = remove_quote(tmp->word);
			tmp = tmp->next;
		}
	}
	redirect_input(fds);
	argv[i] = NULL;
	return (argv);
}
