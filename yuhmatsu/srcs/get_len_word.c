/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:13:58 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/27 22:06:25 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_len_in_singl_quote(char *word, size_t *i, size_t *len)
{
	*i += 1;
	while (word[*i] != '\'')
	{
		*i += 1;
		*len += 1;
	}
	*i += 1;
}

void	get_len_in_double_quote(char *word, size_t *i, size_t *len)
{
	*i += 1;
	while (word[*i] != '\"')
	{
		if (word[*i] == '$')
			free(get_env_len(word, i, len));
		else
		{
			*i += 1;
			*len += 1;
		}
	}
	*i += 1;
}

size_t	get_len_word(char *word)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
			free(get_env_len(word, &i, &len));
		else if (word[i] == '\'')
			get_len_in_singl_quote(word, &i, &len);
		else if (word[i] == '\"')
			get_len_in_double_quote(word, &i, &len);
		else
		{
			i++;
			len++;
		}
	}
	len++;
	return (len);
}
