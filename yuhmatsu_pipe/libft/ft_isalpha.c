/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:57:10 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 03:12:36 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

// #include <ctype.h>

// int main(void)
// {
// 	int a = 'e';
// 	printf("ft_isalpha\n%d", ft_isalpha(a));
// 	printf("\nisalpha\n%d",isalpha(a));
// }