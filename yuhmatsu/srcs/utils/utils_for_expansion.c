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

size_t	token_size(t_token *tok)
{
	t_token	*tmp;
	size_t	size;

	tmp = tok;
	size = 0;
	while (tmp->next != NULL)
	{
		size++;
		tmp = tmp->next;
	}
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