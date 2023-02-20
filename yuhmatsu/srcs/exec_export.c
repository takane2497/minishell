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

#define EXPORT "export: "
#define INVALID_EXPORT "not a valid identifier"

size_t	error_in_export(char *env_str)
{
	//上手く反映されない
	g_all.last_status = 1;
	ft_dprintf(STDERR_FILENO, "%s%s\'%s\'%s\n", \
				ERROR_PREFIX, EXPORT, env_str, INVALID_EXPORT);
	return (1);
}

ssize_t	ft_strchr_pointer(const char *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

size_t	add_env(char *env_str)
{
	ssize_t	pointer_to_equal;
	t_env	*env;
	t_env	*tmp;

	pointer_to_equal = ft_strchr_pointer(env_str, '=');
	if (pointer_to_equal == 0)
		return (error_in_export(env_str));
	tmp = x_malloc(sizeof(t_env));
	if (pointer_to_equal < 0)
	{
		tmp->name = x_strdup(env_str);
		tmp->value = NULL;
	}
	else
	{
		tmp->name = x_strndup(env_str, pointer_to_equal);
		tmp->value = x_strdup(env_str + pointer_to_equal + 1);
	}
	env = g_all.envs;
	while (env != NULL)
		env = env->next;
	env->next = tmp;
	return (0);
}

void	exec_export(char **argv)
{
	t_env	*env;
	size_t	i;

	env = g_all.envs->next;
	if (argv[1] == NULL)
	{
		while (env != NULL)
		{
			if (env->value == NULL)
				printf("declare -x %s\n", env->name);
			else
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
			env = env->next;
		}
		return ;
	}
	i = 1;
	//上手くいってない、、？
	while (argv[i] != NULL)
		add_env(argv[i++]);
}
