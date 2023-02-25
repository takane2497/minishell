/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:38:28 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 03:19:32 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	unsigned char	*d;

	d = (unsigned char *)buf;
	while (n--)
		*(d++) = (unsigned char)ch;
	return (buf);
}

// int main(void)
// {
//         char str[] = "0123456789";
// 		char ft_str[] = "0123456789";

// 		memset(str+2, '*', 5);
//         ft_memset(ft_str+2, '*', 5);

//         printf("%s\n",str);
// 		printf("%s\n",ft_str);

//         return 0;
// }
