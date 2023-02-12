/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:39:01 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/12 09:39:02 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(size_t kind, char *word)
{
	t_token	*tok;

	tok = x_malloc(sizeof(t_token));
	tok->word = word;
	tok->next = NULL;
	tok->kind = kind;
	return (tok);
}

//error codeを258にしないといけない
t_token	*error_hadling_in_tok(char *line, t_token *tok, size_t error_node)
{
	t_token	*tmp;

	while (tok != NULL)
	{
		free(tok->word);
		tmp = tok->next;
		free(tok);
		tok = tmp;
	}
	if (error_node == OPERATOR)
		ft_putendl_fd("minishell: syntax error unexpected token", 2);
	if (error_node == UNCLOSED)
		ft_putendl_fd("minishell: unclosed quote", 2);
	*line = '\0';
	return (tok);
}

size_t	skip_content(char *line, size_t	*tail)
{
	char	key_quote;

	key_quote = line[*tail];
	*tail += 1;
	while (line[*tail] != '\0' && line[*tail] != key_quote)
		*tail += 1;
	if (line[*tail] == '\0')
		return (1);
	return (0);
}

t_token	*my_tokenizer(char *line)
{
	t_token	*tok;
	t_token	*tok_head;
	size_t	head;
	size_t	tail;

	tok_head = new_token(TK_START, NULL);
	tok = tok_head;
	head = 0;
	while (line[head] != '\0')
	{
		while (is_space(line, head))
			head++;
		tail = head;
		if (line[head] == '\0')
			break ;
		while (line[tail] != '\0' && is_space(line, tail) == 0)
		{
			if (is_operator(line + tail) == 3)
				return (error_hadling_in_tok(line + tail, tok_head, OPERATOR));
			else if (is_operator(line + tail) && head == tail)
			{
				tail += is_operator(line + tail);
				break ;
			}
			else if (is_operator(line + tail))
				break ;
			else if ((line[tail] == '\'' || line[tail] == '\"') \
					&& skip_content(line, &tail))
				return (error_hadling_in_tok(line + tail, tok_head, UNCLOSED));
			tail++;
		}
		tok->next = new_token(TK_WORD, x_strndup(line + head, tail - head));
		tok = tok->next;
		head = tail;
	}
	return (tok_head);
}
