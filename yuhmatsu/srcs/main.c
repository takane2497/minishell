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

t_env	*init_new_env(char	*env_str)
{
	t_env	*env;
	ssize_t	pointer_to_equal;

	env = x_malloc(sizeof(t_env));
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
	t_env		*head;
	extern char	**environ;

	i = 0;
	g_all.last_status = 0;
	g_all.now_pwd = getcwd(NULL, 0);
	g_all.envs = init_new_env(NULL);
	tmp = g_all.envs;
	head = tmp;
	if (g_all.now_pwd == NULL)
	{
		perror("pwd init");
		exit(1);
	}
	while (environ[i] == NULL)
		i++;
	g_all.environ = x_calloc(i + 1, sizeof(char *));
	i = 0;
	while (environ[i] != NULL)
	{
		g_all.environ[i] = strdup(environ[i]);
		printf("environ = %s\n", g_all.environ[i]);
		tmp->next = init_new_env(environ[i]);
		tmp = tmp->next;
		printf("tmp name= %s\n", tmp->name);
		printf("tmp value = %s\n", tmp->value);
		printf("head value = %s\n", head->next->value);
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
	while (env != NULL)
	{
		printf("%s\n", env->name);
		env = env->next;
	}
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
