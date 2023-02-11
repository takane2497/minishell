/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:51:34 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 06:11:05 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	if (s < d)
		while (n--)
			d[n] = s[n];
	else
		ft_memcpy (d, s, n);
	return (dest);
}

// int main()
// {

// 	char str[] = "abcdefghijklmdeopqrstu";

//         printf("移動前：%s\n",str);

//         ft_memmove(str+5, str, 10);

//         printf("移動後：%s\n",str);

//         return 0;
// }
