/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:11:16 by takonaga          #+#    #+#             */
/*   Updated: 2023/03/06 22:44:44 by yuhmatsu         ###   ########.fr       */
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

char	*my_getcwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd init");
		exit(1);
	}
	return (pwd);
}

// void	update_shell_level(void)
// {
// 	char	*shlvl;
// 	int		shell_level;
// }

void	init_global(void)
{
	size_t		i;
	t_env		*tmp;
	extern char	**environ;

	i = 0;
	g_all.last_status = 0;
	g_all.now_pwd = my_getcwd();
	g_all.envs = init_new_env(NULL);
	tmp = g_all.envs;
	if (environ == NULL)
		return ;
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
	// update_shell_level();
}

int	interpret(char *const line)
{
	char	**argv;
	t_token	*tok;
	t_token	*tok_head;
	t_fds	fds;

	fds.i = 0;
	tok_head = new_token(NULL);
	tok = my_tokenizer(line, tok_head);
	if (tok == NULL)
		return (ERROR_TOKENIZE);
	fds.num_pipe = count_pipe(tok_head);
	while (tok != NULL)
	{
		fds.now_input_fd = 0;
		fds.now_output_fd = 1;
		argv = expansion(&tok, &fds.now_input_fd, &fds.now_output_fd);
		if (argv == NULL || fds.now_input_fd == -1)
			return (free_argv_token(argv, tok_head) + 1);
		g_all.last_pid = exec(argv, &fds.i, &fds);
		free_argv(argv);
	}
	if (0 < fds.i)
		g_all.last_status = all_wait(fds.i);
	free_tok(tok_head);
	return (g_all.last_status);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	init_global();
	init_signal();
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
	ft_dprintf(STDERR_FILENO, "\e[Aminishell$ exit\n");
	exit(1);
}
