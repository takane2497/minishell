/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:31:11 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/28 21:40:34 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define EXPORT "export: "
#define INVALID_EXPORT "not a valid identifier"

size_t	error_in_export(char *env_str)
{
	g_all.last_status = 1;
	ft_dprintf(STDERR_FILENO, "%s%s\'%s\': %s\n", \
				ERROR_PREFIX, EXPORT, env_str, INVALID_EXPORT);
	return (1);
}

ssize_t	check_name_and_return_to_eq_index(const char *str)
{
	ssize_t	i;

	i = 0;
	if (!(is_alpha_under(str[i])))
		return (0);
	while (is_alpha_num_under(str[i]))
		i++;
	if (str[i] == '=')
		return (i);
	else if (str[i] == '\0')
		return (-1);
	else
		return (0);
}

t_env	*add_env(char *env_str, ssize_t pointer_to_equal)
{
	t_env	*tmp;

	tmp = x_calloc(1, sizeof(t_env));
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
	return (tmp);
}

size_t	set_env(char *env_str, char *new_value)
{
	ssize_t	pointer_to_equal;
	t_env	*env;

	pointer_to_equal = check_name_and_return_to_eq_index(env_str);
	if (pointer_to_equal == 0)
		return (error_in_export(env_str));
	if (0 < pointer_to_equal)
		env_str[pointer_to_equal] = '\0';
	env = g_all.envs->next;
	while (env->next != NULL || ft_strcmp(env_str, env->name) == 0)
	{
		if (ft_strcmp(env_str, env->name) == 0)
		{
			if (0 < pointer_to_equal || new_value != NULL)
				free(env->value);
			if (0 < pointer_to_equal && new_value == NULL)
				env->value = x_strdup(env_str + pointer_to_equal + 1);
			if (new_value != NULL)
				env->value = x_strdup(new_value);
			return (0);
		}
		env = env->next;
	}
	env->next = add_env(env_str, pointer_to_equal);
	return (0);
}

int	exec_export(char **argv)
{
	t_env	*env;
	size_t	i;

	g_all.last_status = 0;
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
		return (g_all.last_status);
	}
	i = 1;
	while (argv[i] != NULL)
		set_env(argv[i++], NULL);
	return (g_all.last_status);
}
