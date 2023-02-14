/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:19:48 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/12 22:19:49 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	token_size(t_token *tok, int **output_fds)
{
	t_token	*tmp;
	size_t	size;
	size_t	output_count;

	tmp = tok;
	size = 0;
	output_count = 0;
	while (tmp != NULL)
	{
		if (tmp->kind == TK_WORD)
			size++;
		if (tmp->kind == TK_OUTPUT || tmp->kind == TK_ADD_OUTPUT)
		{
			output_count++;
			tmp = tmp->next;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	if (output_count == 0)
		*output_fds = NULL;
	else
		*output_fds = x_calloc(output_count + 1, sizeof(int));
	return (size);
}

void	free_argv_token(char **argv, t_token *tok)
{
	size_t	i;
	t_token	*tmp;

	while (tok != NULL)
	{
		free(tok->word);
		tmp = tok->next;
		free(tok);
		tok = tmp;
	}
	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

size_t	my_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;

	if (dst == NULL)
		return (0);
	d_len = ft_strlen(dst);
	if (src == NULL)
		return (d_len);
	s_len = ft_strlen(src);
	if (dstsize <= d_len)
		return (s_len + dstsize);
	ft_strlcpy(&dst[d_len], src, dstsize - d_len);
	return (d_len + s_len);
}
