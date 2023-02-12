/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:15:43 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/12 23:15:44 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fatal_error(const char *msg)
{
	ft_putstr_fd("Fatal Error: ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}

void	err_exit(const char *location, const char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)location, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(status);
}
