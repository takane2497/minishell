/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 20:12:11 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 06:41:57 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

// int main(void)
// {
// 	char *dest = NULL;
// 	char *src =  "abc";
// 	ft_memcpy(dest, src, 4);
// 	printf("%s\n", dest);
// 	char *dest2 = NULL;
// 	char *src2 = "abc";
// 	memcpy(dest2, src2, 4);
// 	printf("%s\n", dest2);
// }
