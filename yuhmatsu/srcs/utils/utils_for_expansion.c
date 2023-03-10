/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:19:48 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/22 01:31:58 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *word)
{
	t_token	*tok;

	tok = x_malloc(sizeof(t_token));
	tok->word = word;
	tok->next = NULL;
	if (word == NULL)
		tok->kind = TK_START;
	else if (is_operator(word))
		tok->kind = get_kinds(word);
	else
		tok->kind = TK_WORD;
	return (tok);
}

size_t	token_size(t_token *tok, size_t *size)
{
	t_token	*tmp;
	size_t	i;

	tmp = tok->next;
	i = 1;
	while (tmp != NULL && tmp->kind != TK_PIPE)
	{
		if (tmp->kind == TK_WORD)
			i++;
		if (tmp->kind == TK_INPUT || tmp->kind == TK_DELIMITER)
			tmp = tmp->next;
		if (tmp->kind == TK_OUTPUT || tmp->kind == TK_ADD_OUTPUT)
			tmp = tmp->next;
		if (tmp != NULL)
			tmp = tmp->next;
	}
	*size = i;
	if (i == 0)
		return (1);
	return (0);
}

size_t	my_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;

	if (dst == NULL)
		return (0);
	d_len = ft_strlen(dst);
	if (src == NULL || *src == '\0')
	{
		free(src);
		return (d_len);
	}
	s_len = ft_strlen(src);
	if (dstsize <= d_len)
	{
		free(src);
		return (s_len + dstsize);
	}
	ft_strlcpy(&dst[d_len], src, dstsize - d_len);
	free(src);
	return (d_len + s_len);
}

size_t	init_expansion(char ***argv, t_token **tmp, size_t *i, t_token *tok)
{
	size_t	size;

	if (token_size(tok, &size))
		return (1);
	*argv = x_calloc((size + 1), sizeof(char *));
	*tmp = tok->next;
	*i = 0;
	return (0);
}
