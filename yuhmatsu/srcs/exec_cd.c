/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 01:19:37 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/22 01:39:13 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cd(char **argv)
{
	char	*old_pwd;
	char	*pwd;

	if (argv[1] == NULL)
	{
		pwd = x_getenv("HOME");
	}
	old_pwd = x_getenv("PWD");
	if (old_pwd == NULL)
		old_pwd = x_calloc(1, sizeof(char));
	set_env("OLDPWD", old_pwd);
}