/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <takonaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:00:13 by takonaga          #+#    #+#             */
/*   Updated: 2022/10/22 17:04:03 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *seek, size_t len)
{
	size_t	seek_len;
	size_t	i;

	if (str == NULL || seek == NULL)
		return (NULL);
	if (*seek == '\0')
		return ((char *)str);
	seek_len = ft_strlen(seek);
	i = 0;
	while (str[i] != '\0' && i + seek_len <= len)
	{
		if (!(ft_strncmp(&str[i], seek, seek_len)))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	printf("%s\n", strnstr(NULL, "aiu", 0));
// }