/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:40:22 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/21 06:06:02 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static size_t	digits_count(long tmp)
{
	size_t	count;

	count = 0;
	while (tmp != 0)
	{
		tmp /= 10;
		count++;
	}
	return (count);
}

static void	calculation(long tmp, char *ret, size_t count, size_t *cycle)
{
	int64_t	s1;
	int64_t	s2;
	char	c;

	s1 = tmp / 10;
	s2 = tmp % 10;
	if (s1 != 0)
	{
		calculation(s1, ret, count, cycle);
		ret += *cycle;
	}
	c = s2 + '0';
	*ret = c;
	*cycle += 1;
}

char	*ft_itoa(int n)
{
	int64_t	tmp;
	size_t	count;
	char	*ret;
	size_t	cycle;

	tmp = n;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		tmp = -tmp;
	count = digits_count(tmp);
	if (n < 0)
		count++;
	ret = (char *)ft_calloc(count +1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	if (n < 0)
		*ret++ = '-';
	cycle = 0;
	calculation(tmp, ret, count, &cycle);
	if (n < 0)
		return (ret - 1);
	return (ret);
}
