/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:36:56 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/22 21:54:31 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *str, char c)
{
	size_t	i;
	size_t	num_word;

	i = 0;
	num_word = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			num_word++;
		}
	}
	return (num_word);
}

char	*next_str(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	s = s + i;
	return (s);
}

static char	**allfree(char **rtn_str)
{
	size_t	i;

	i = 0;
	while (rtn_str[i] != NULL)
	{
		free(rtn_str[i]);
		i++;
	}
	free(rtn_str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result_str;
	size_t	i;
	size_t	j;
	size_t	word;

	if (s == NULL)
		return (NULL);
	word = count_word(s, c);
	result_str = (char **) malloc (sizeof(char *) * (word + 1));
	if (result_str == NULL)
		return (NULL);
	j = 0;
	while (j < word)
	{
		i = 0;
		s = next_str((char *)s, c);
		while (((char *)s)[i] != '\0' && ((char *)s)[i] != c)
			i++;
		result_str[j] = ft_substr(s, 0, i);
		if (result_str[j++] == NULL)
			return (allfree(result_str));
		s = s + i;
	}
	result_str[j] = NULL;
	return (result_str);
}

// int main(int argc, char **argv) {
// 	if (argc == 2) {
// 		char **strs = ft_split(argv[1], ' ');
// 		if (strs == NULL) {
// 			fprintf(stderr, "Error\n");
// 			return 1;
// 		}
// 		size_t i = 0;
// 		for (; strs[i]; i++) {
// 			printf("%s\n", strs[i]);
// 			free(strs[i]);
// 		}
// 		free(strs);
// 	}
// }
