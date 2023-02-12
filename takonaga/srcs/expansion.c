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

char	**expansion(t_token *tok)
{
	char	**argv;
	size_t	size;
	size_t	i;

	size = token_size(tok);
	if (size == 0)
		return (NULL);
	argv = x_malloc((size + 1) * sizeof(char *));
	tok = tok->next;
	i = 0;
	while (i < size)
	{
		argv[i] = tok->word;
		tok = tok->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
