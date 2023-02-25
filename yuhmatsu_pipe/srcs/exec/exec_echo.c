/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:11:54 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/21 15:27:09 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(char **argv)
{
	size_t	i;
	size_t	flag_new_line;
	size_t	flag_string;

	i = 1;
	flag_new_line = 1;
	flag_string = 0;
	while (argv[i] != NULL)
	{
		if (flag_string == 0 && ft_strncmp("-n", argv[i], 2) == 0)
			flag_new_line = 0;
		if (ft_strncmp("-n", argv[i], 2) != 0)
			flag_string = 1;
		if (flag_string == 1)
			ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i] != NULL && flag_string == 1)
			ft_putchar_fd(' ', 1);
	}
	if (flag_new_line == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}
