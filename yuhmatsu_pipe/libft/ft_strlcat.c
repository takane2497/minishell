/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:49:35 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/22 17:17:33 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;

	s_len = ft_strlen(src);
	if (dst == NULL)
		return (s_len);
	d_len = ft_strlen(dst);
	if (dstsize <= d_len)
		return (s_len + dstsize);
	ft_strlcpy(&dst[d_len], src, dstsize - d_len);
	return (d_len + s_len);
}

// int	main(void)
// {
// 	char src1[100] = "takonaga";
// 	char dest1[100] = "aaaaaa";
// 	char src2[100] = "takonaga";
// 	char dest2[100] = "aaaaaa";
// 	unsigned  int	size;

// 	size = 100;
// 	printf("mk: %zu\n", ft_strlcat(dest1, src1, size));
// 	printf("mk: %s\n", dest1);
// 	printf("or: %zu\n", strlcat(dest2, src2, size));
// 	printf("or: %s\n", dest2);

// 	return (0);
// }
