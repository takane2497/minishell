/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:59:52 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 07:07:31 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || (ft_isdigit(c)));
}

// #include <ctype.h>

// int	main(void)
// {
// 	int a = 'e';
// 	printf("ft_isalnum\n%d",ft_isalnum(a));
// 	printf("\nisalnum\n%d",isalnum(a));
// }

//