/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 04:51:25 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/10 06:38:45 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// int main(void)
// {
// 	int	ft_len;
// 	int	len;
//     char	s[] = "today";

//     ft_len	= ft_strlen(s);
// 	len	= strlen(s);
//     printf("\"%s\" は %d 文字\n", s, ft_len);
// 	printf("\"%s\" は %d 文字\n", s, len);

//     printf("\"%s\" は %zu 文字\n", "hello world", ft_strlen("hello world"));
// 	printf("\"%s\" は %zu 文字\n", "hello world", strlen("hello world"));

//     return 0;
// }
