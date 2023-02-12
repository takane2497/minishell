/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:01:08 by takonaga          #+#    #+#             */
/*   Updated: 2023/02/12 14:01:09 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	size_t	i;

	if (s1 == NULL || n == 0)
		return (NULL);
	i = 0;
	p = x_malloc(ft_strlen(s1));
	if (p == NULL)
		return (NULL);
	while (s1 && s1[i] && i < n)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
