/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:00:04 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 03:14:54 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (32 <= c && c <= 126);
}

// #include <ctype.h>

// int main(void)
// {
// 	int	a = 'd';
// 	printf("ft_isprint\n%d", ft_isprint(a));
// 	printf("\nisprint\n%d",isprint(a));
// }
