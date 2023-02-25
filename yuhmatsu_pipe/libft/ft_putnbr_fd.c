/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 05:30:39 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/22 15:06:11 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int64_t	int_n;

	int_n = n;
	if (int_n < 0)
	{
		ft_putchar_fd('-', fd);
		int_n *= -1;
	}
	if (int_n >= 10)
	{
		ft_putnbr_fd(int_n / 10, fd);
		ft_putnbr_fd(int_n % 10, fd);
	}
	else
		ft_putchar_fd(int_n + '0', fd);
}
