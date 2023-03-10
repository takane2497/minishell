/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:06:05 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/22 00:38:57 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_pwd(char **argv)
{
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
		printf("%s\n", g_all.now_pwd);
	return (0);
}
