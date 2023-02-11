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


void	fatal_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	ft_putstr_fd("Fatal Error: ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}

void	err_exit(const char *location, const char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)location, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(status);
}


char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;


	value = getenv("PATH");
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PASS_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			dup = ft_strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "No such file or directory", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

int	exec(char *argv[])
{
	extern char **environ;
	const char	*path = argv[0];
 	pid_t	pid;
	int 	wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

int	interpret(char *const line)
{
	int status;
	char *argv[] = {line, "hello world", NULL};

	status = exec(argv);
	return (status);
}

int main(void)
{
	int	status;
	char *line;

	rl_outstream = stderr;
	status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (!*line)
			continue;
		if (*line)
			add_history(line);
		status = interpret(line);
		free(line);
	}
	exit(status);
}