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

char	*reverse_str(int num, int *str_len)
{
	char	numstr[NUM_STR_LEN];
	char	temp;
	int		j;
	int		k;

	*str_len = 0;
	while (num > 0)
	{
		numstr[(*str_len)++] = (num % 10) + '0';
		num /= 10;
	}
	j = 0;
	k = *str_len - 1;
	while (j < k)
	{
		temp = numstr[j];
		numstr[j++] = numstr[k];
		numstr[k--] = temp;
	}
	if (*str_len == 0)
		numstr[(*str_len)++] = '0';
	numstr[*str_len] = '\0';
	return (x_strdup(numstr));
}

char	*get_special_env(char *word, size_t *i, size_t *len)
{
	int		str_len;
	char	*numstr;

	if (word[*i] == '0')
	{
		if (len != NULL)
			*len += 9;
		*i += 1;
		return (x_strdup("minishell"));
	}
	if (word[*i] == '?')
	{
		if (last_status == -1)
			return (NULL);
		numstr = reverse_str(last_status, &str_len);
		if (len != NULL)
			*len += str_len;
		*i += 1;
		return (numstr);
	}
	return (NULL);
}

char	*get_env_len(char *word, size_t *i, size_t *len)
{
	char	tmp;
	char	*ans;
	size_t	start;

	*i += 1;
	start = *i;
	if (word[*i] == '0' || word[*i] == '?')
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
	ans = x_strdup(getenv(word + start));
	word[*i] = tmp;
	if (len != NULL && ans != NULL)
		*len += ft_strlen(ans);
	return (ans);
}
