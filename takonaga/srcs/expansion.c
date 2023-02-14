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
	str = x_calloc(len, sizeof(char));
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

char	**expansion(t_token *tok)
{
	char	**argv;
	size_t	size;
	size_t	i;

	size = token_size(tok);
	if (size == 0)
		return (NULL);
	argv = x_calloc((size + 1), sizeof(char *));
	tok = tok->next;
	i = 0;
	while (i < size)
	{
		argv[i] = remove_quote(tok->word);
		tok = tok->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
