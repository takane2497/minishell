/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 07:22:11 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/16 06:08:52 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			tmp = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (tmp);
}

// int main(void)
// {
// 	char a[] = "abcdefghijkabcdefghij";
// 	int b = 'c';
// 	printf("%s\n", strrchr(a, b));
// 	char c[] = "abcdefghigkabcdefghij";
// 	int d = 'c';
// 	printf("%s\n", ft_strrchr(c, d));
// }