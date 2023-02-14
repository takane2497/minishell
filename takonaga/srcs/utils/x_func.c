/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_func.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:15:46 by takonaga          #+#    #+#             */
/*   Updated: 2023/02/12 10:15:48 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*x_malloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (tmp == 0)
	{
		perror("malloc");
		exit(1);
	}
	return (tmp);
}

void	*x_calloc(size_t count, size_t size)
{
	char	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == 0)
	{
		perror("calloc");
		exit(1);
	}
	return (tmp);
}

char	*x_strdup(char *str)
{
	char	*line;

	if (!str)
		return (NULL);
	line = ft_strdup(str);
	if (line == NULL)
	{
		perror("malloc error");
		exit(1);
	}
	return (line);
}

char	*x_strndup(char *str, size_t len)
{
	char	*line;

	line = ft_strndup(str, len);
	if (line == NULL)
	{
		perror("malloc error");
		exit(1);
	}
	return (line);
}
