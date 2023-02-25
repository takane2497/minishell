/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:22:55 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/23 11:11:13 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_current_dir1(char *new_pwd, size_t *i, size_t *j)
{
	*ft_strrchr(g_all.now_pwd, '/') = '\0';
	while (g_all.now_pwd[*i] != '\0')
	{
		new_pwd[*i] = g_all.now_pwd[*j];
		*i += 1;
		*j += 1;
	}
	*j = 2;
}

void	init_current_dir2(char *new_pwd, char *pwd, size_t *i, size_t *j)
{
	while (g_all.now_pwd[*i] != '\0')
	{
		new_pwd[*i] = g_all.now_pwd[*j];
		*i += 1;
		*j += 1;
	}
	*j = 1;
	if (ft_strncmp(pwd, ".", 1) != 0)
		*j = 0;
}

void	move_back_dir(char *new_pwd, size_t *flag, size_t *i, size_t *j)
{
	if (0 < *i && new_pwd[*i - 1] != '/')
		*i -= 1;
	while (0 < *i && new_pwd[*i] != '/')
		*i -= 1;
	*j += 3;
	*flag = 1;
}

void	stay_dir(char *pwd, size_t *j)
{
	*j += 1;
	if (pwd[*j] == '/')
		*j += 1;
}

void	handle_slash(size_t	*flag, size_t *j)
{
	*j += 1;
	*flag = 1;
}
