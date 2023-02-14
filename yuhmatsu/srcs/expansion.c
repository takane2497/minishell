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

t_token	*redirect_output(t_token *tmp, int *output_fds, size_t *j)
{
	char	*str;
	int		tmp_fd;

	str = remove_quote(tmp->next->word);
	if (tmp->kind == TK_ADD_OUTPUT)
		tmp_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, \
					S_IWUSR | S_IRUSR);
	else
		tmp_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, \
					S_IWUSR | S_IRUSR);
	free(str);
	output_fds[*j] = dup(1);
	*j += 1;
	dup2(tmp_fd, 1);
	tmp = tmp->next->next;
	return (tmp);
}

char	**expansion(t_token *tok, int **output_fds)
{
	char	**argv;
	size_t	size;
	size_t	i;
	size_t	j;
	t_token	*tmp;

	size = token_size(tok, output_fds);
	if (size == 0)
		return (NULL);
	argv = x_malloc((size + 1) * sizeof(char *));
	tmp = tok->next;
	i = 0;
	j = 0;
	while (tmp != NULL)
	{
		if (tmp->kind == TK_OUTPUT || tmp->kind == TK_ADD_OUTPUT)
			tmp = redirect_output(tmp, *output_fds, &j);
		else if (tmp->kind == TK_WORD)
		{
			argv[i++] = remove_quote(tmp->word);
			tmp = tmp->next;
		}
	}
	argv[i] = NULL;
	return (argv);
}
