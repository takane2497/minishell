/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 07:33:06 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/16 06:08:54 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

// int main(void)
// {
// 	char a[] = "abcdefghijk";
// 	int b = '\0';
// 	printf("%s\n", strchr(a, b));
// 	char c[] = "abcdefghigk";
// 	int d = '\0';
// 	printf("%s\n", ft_strchr(c, d));
// }