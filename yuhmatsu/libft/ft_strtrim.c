/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:26:50 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/21 07:25:32 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checker(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && ft_checker(s1[i], set))
		i++;
	while (len > i && ft_checker(s1[len - 1], set))
		len--;
	str = malloc(sizeof(char) * (len - i + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}

// #include <stdio.h>
// int main(void)
// {
// 	char s1[] = "1234AA1A1234";
// 	char set[] = "1234";
// 	printf("%s\n", ft_strtrim(s1, set));
// 	// printf("%s\n", ft_strtrim("abcdba", "acb"));
// 	// printf("%s\n", "");
// 	// return (0);
// }
