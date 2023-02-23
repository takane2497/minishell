/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:23:18 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/29 07:44:23 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_nb(int fd, int n)
{
	int		len;
	char	*nb;

	len = 0;
	nb = ft_itoa(n);
	len = print_str(fd, nb);
	free(nb);
	return (len);
}
