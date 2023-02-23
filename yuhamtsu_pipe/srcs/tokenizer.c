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

size_t	skip(char *line, size_t	*tail)
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

bool	check_operator_error(t_token *tok)
{
	t_token	*tmp;

	tmp = tok->next;
	while (tmp != NULL)
	{
		if (tmp->kind != TK_WORD && \
			(tmp->next == NULL || tmp->next->kind != TK_WORD))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

size_t	skip_space_etc(char *line, size_t *head, size_t *tail, t_token **tok)
{
	if (*tail != 0)
	{
		*tail += is_operator(line + *tail) * (*head == *tail);
		(*tok)->next = new_token(x_strndup(line + *head, *tail - *head));
		*tok = (*tok)->next;
		*head = *tail;
	}
	while (is_space(line, *head))
			*head += 1;
		*tail = *head;
	if (line[*head] == '\0')
		return (1);
	else
		return (0);
}

t_token	*my_tokenizer(char *line, t_token *tok_head)
{
	t_token	*tok;
	size_t	head;
	size_t	tail;

	tok = tok_head;
	head = 0;
	tail = 0;
	while (line[head] != '\0')
	{
		while (line[tail] != '\0' && is_space(line, tail) == 0)
		{
			if (is_operator(line + tail) == 3)
				return (error_hadling_in_tok(line + tail, tok_head, OPERATOR));
			if (is_operator(line + tail))
				break ;
			if ((line[tail] == '\'' || line[tail] == '\"') && skip(line, &tail))
				return (error_hadling_in_tok(line + tail, tok_head, UNCLOSED));
			tail++;
		}
		if (skip_space_etc(line, &head, &tail, &tok))
			break ;
	}
	if (check_operator_error(tok_head))
		return (error_hadling_in_tok(line, tok_head, OPERATOR));
	return (tok_head);
}
