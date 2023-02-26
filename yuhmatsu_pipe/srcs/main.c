/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:11:16 by takonaga          #+#    #+#             */
/*   Updated: 2023/02/09 18:11:19 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all	g_all;

t_env	*init_new_env(char *env_str)
{
	t_env	*env;
	ssize_t	pointer_to_equal;

	env = x_calloc(1, sizeof(t_env));
	if (env_str == NULL)
	{
		env->name = NULL;
		env->value = NULL;
	}
	else
	{
		pointer_to_equal = ft_strchr_pointer(env_str, '=');
		if (pointer_to_equal < 0)
		{
			env->name = x_strdup(env_str);
			env->value = NULL;
		}
		else
		{
			env->name = x_strndup(env_str, pointer_to_equal);
			env->value = x_strdup(env_str + pointer_to_equal + 1);
		}
	}
	env->next = NULL;
	return (env);
}

void	init_global(void)
{
	size_t		i;
	t_env		*tmp;
	extern char	**environ;

	i = 0;
	g_all.last_status = 0;
	g_all.now_pwd = getcwd(NULL, 0);
	g_all.envs = init_new_env(NULL);
	tmp = g_all.envs;
	if (g_all.now_pwd == NULL)
	{
		perror("pwd init");
		exit(1);
	}
	while (environ[i] != NULL)
		i++;
	g_all.environ = x_calloc(i + 1, sizeof(char *));
	i = 0;
	while (environ[i] != NULL)
	{
		g_all.environ[i] = x_strdup(environ[i]);
		tmp->next = init_new_env(g_all.environ[i]);
		tmp = tmp->next;
		i++;
	}
}

int	main(void)
{
	char	*line;
	t_env	*env;

	rl_outstream = stderr;
	init_global();
	env = g_all.envs;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (!*line)
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		g_all.last_status = interpret(line);
		free(line);
	}
	exit(g_all.last_status);
}
