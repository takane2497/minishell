/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:03:28 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/22 02:12:06 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_env(void)
{
	t_env	*env;

	env = g_all.envs->next;
	while (env != NULL)
	{
		if (env->value != NULL && ft_strcmp(env->name, "_") != 0)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
