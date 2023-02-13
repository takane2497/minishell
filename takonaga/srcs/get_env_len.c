/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:08:55 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/12 22:08:57 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//incomplete function
char	*get_special_env(char *word, size_t *i, size_t *len)
{
	if (word[*i] == '0')
	{
		if (len != NULL)
			*len += 9;
		*i += 1;
		return ("minishell");
	}
	if (word[*i] == '?')
	{

	}
	return (NULL);
}

char	*get_env_len(char *word, size_t *i, size_t *len)
{
	size_t	env_len;
	char	tmp;
	char	*ans;
	size_t	start;

	env_len = 0;
	*i += 1;
	start = *i;
	if (word[*i] == '$' || word[*i] == '0' || word[*i] == '?')
		return (get_special_env(word, i, len));
	if (!(is_alpha_under(word[*i])))
	{
		if (word[*i] != '\0')
			*i += 1;
		return (NULL);
	}
	while (is_alpha_num_under(word[*i]))
		*i += 1;
	tmp = word[*i];
	word[*i] = '\0';
	ans = getenv(word + start);
	word[*i] = tmp;
	if (len != NULL && ans != NULL)
		*len += ft_strlen(ans);
	return (ans);
}
