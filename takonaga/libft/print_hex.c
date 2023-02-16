/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 04:07:19 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/29 07:03:21 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	hex_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

static	void	put_hex(unsigned int nb, const char format)
{
	if (nb >= 16)
	{
		put_hex(nb / 16, format);
		put_hex(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			put_char(1, (nb + '0'));
		else
		{
			if (format == 'x')
				put_char(1, (nb - 10 + 'a'));
			if (format == 'X')
				put_char(1, (nb -10 + 'A'));
		}
	}
}

int	print_hex(unsigned int nb, const char format)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		put_hex(nb, format);
	return (hex_len(nb));
}
