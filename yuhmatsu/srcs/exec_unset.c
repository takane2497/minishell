/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:42:58 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/22 01:11:03 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_unset(char **argv)
{
	t_env	*env;
	t_env	*tmp;
	size_t	i;

	i = 1;
	while (argv[i] != NULL)
	{
		env = g_all.envs;
		while (env->next != NULL)
		{
			if (ft_strcmp(argv[i], env->next->name) == 0)
			{
				tmp = env->next->next;
				free(env->next->name);
				free(env->next->value);
				free(env->next);
				env->next =tmp;
				break ;
			}
			env = env->next;
		}
		i++;
	}
	return (0);
}