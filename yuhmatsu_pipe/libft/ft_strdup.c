/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 07:19:00 by takonaga          #+#    #+#             */
/*   Updated: 2023/02/23 11:11:38 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	s1_len;

	if (s1 == NULL)
		return (NULL);
	s1_len = (ft_strlen(s1));
	dest = ft_calloc(s1_len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, s1_len + 1);
	return (dest);
}
