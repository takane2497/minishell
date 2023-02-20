/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:31:11 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/20 19:31:12 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_export(char **argv)
{
	t_env	*env;

	env = g_all.envs->next;
	if (argv[1] == NULL)
	{
		while (env != NULL)
		{
			if (env->value != NULL)
				printf("declare -x %s\n", env->name);
			else
				printf("declare -x %s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
}
