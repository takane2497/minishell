/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:58:52 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 06:38:39 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0 ;
	if (dstsize == 0)
		return (src_len);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// int main(void)
// {
// 	char a[10] = "abcdefg";
// 	char b[] = "TTTTTTTK";
// 	printf("%zu\n", ft_strlcpy(a, b, 8));
// 	printf("%s\n", a);
// 	char c[10] = "abcdefg";
// 	char d[] = "TTTTTTTK";
// 	printf("%zu\n", strlcpy(c, d, 8));
// 	printf("%s\n", c);
// }
