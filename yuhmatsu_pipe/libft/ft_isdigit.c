/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:52:23 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 03:14:36 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

// #include <ctype.h>

// int main(void)
// {
// 	int a = '2';
// 	printf("ft_isalpha\n%d", ft_isdigit(a));
// 	printf("\nisalpha\n%d",isdigit(a));
// }
