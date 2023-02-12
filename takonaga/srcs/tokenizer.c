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

size_t	is_space(char *line, size_t i)
{
	return (line[i] == ' ' || line[i] == '\t' || line[i] == '\n');
}

size_t	is_operator(char *line)
{
	if (ft_strncmp(line, "||", 2) == 0)
		return (3);
	if (ft_strncmp(line, "|", 1) == 0)
		return (1);
	if (ft_strncmp(line, ">>>", 3) == 0)
		return (3);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	if (ft_strncmp(line, "<<<", 3) == 0)
		return (3);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(line, "<", 1) == 0)
		return (1);
	return (0);
}

//free token
t_token	*operator_error(char *line, t_token *tok)
{
	tok = NULL;
	*line = '\0';
	return (tok);
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
				return (operator_error(line + tail, tok_head));
			else if (is_operator(line + tail) && head == tail)
			{
				tail += is_operator(line + tail);
				break ;
			}
			else if (is_operator(line + tail))
				break ;
			tail++;
		}
		tok->next = new_token(TK_WORD, x_strndup(line + head, tail - head));
		tok = tok->next;
		head = tail;
	}
	return (tok_head);
}
