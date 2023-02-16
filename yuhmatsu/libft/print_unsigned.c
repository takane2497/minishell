/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 07:49:40 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/29 09:06:47 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static	char	*uitoa(unsigned int n)
{
	char	*nb;
	int		len;

	len = nb_len(n);
	nb = (char *)malloc(sizeof(char) * (len +1));
	if (!nb)
		return (0);
	nb[len] = '\0';
	while (n != 0)
	{
		nb[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (nb);
}

int	print_unsigned(unsigned int n)
{
	int		len;
	char	*nb;

	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		nb = uitoa(n);
		len += print_str(nb);
		free(nb);
	}
	return (len);
}
