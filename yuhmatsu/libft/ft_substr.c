/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 02:07:50 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/22 18:23:22 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	s_len = (ft_strlen(s));
	if (len == 0 || s_len <= start)
		return (ft_strdup(""));
	else if (len > s_len - start)
		len = s_len - start;
	len++;
	substr = (char *)malloc(sizeof(char) * len);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, len);
	return (substr);
}
