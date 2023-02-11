/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:22:21 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 03:13:52 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}

// #include <ctype.h>

// int	main(void)
// {
// 	int a = ' ';
// 	printf("ft_isascill\n%d", ft_isascill(a));
// 	printf("\nisascill\n%d",isascii(a));
// }
