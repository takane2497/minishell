/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:32:56 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/22 15:33:05 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (s1 == NULL || s2 == NULL || n == 0)
		return (0);
	while (i < n - 1 && *(str1 + i) == *(str2 + i))
		++i;
	return (*(str1 + i) - *(str2 + i));
}

// int main()
// {
//         printf("%d\n", ft_memcmp("abc\0def", "abc\0def", 7));
//         printf("%d\n", ft_memcmp("abc\0def", "aBc\0def", 7));
//         printf("%d\n", ft_memcmp("AcB", "abc\0d", 8));
// 		printf("%d\n", memcmp("AcB", "abc\0d", 8));
// }