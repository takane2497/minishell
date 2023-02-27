/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 01:19:37 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/23 11:28:16 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_error(char *error_message1, char *error_message2, char *pwd)
{
	if (pwd != NULL)
	{
		free(pwd);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (error_message2 == NULL)
		ft_dprintf(STDERR_FILENO, "%scd: %s\n", ERROR_PREFIX, error_message1);
	else
		ft_dprintf(STDERR_FILENO, "%scd: %s: %s\n", ERROR_PREFIX, \
					error_message1, error_message2);
	return (1);
}

char	*handle_end_of_sentence(char *new_pwd, char *pwd, size_t *i)
{
	char	*ans;

	free(pwd);
	if (*i == 0)
	{
		new_pwd[*i] = '/';
		*i += 1;
	}
	if (1 < *i && new_pwd[*i - 1] == '/')
		*i -= 1;
	new_pwd[*i] = '\0';
	ans = x_strdup(new_pwd);
	free(new_pwd);
	return (ans);
}

char	*get_now_pwd(char *pwd, size_t i, size_t j, size_t flag)
{
	char	*new_pwd;

	new_pwd = x_calloc(PATH_MAX, sizeof(char));
	if (ft_strncmp(pwd, "..", 2) == 0)
		init_current_dir1(new_pwd, &i, &j);
	else if (ft_strncmp(pwd, ".", 1) == 0 || ft_strncmp(pwd, "/", 1) != 0)
		init_current_dir2(new_pwd, pwd, &i, &j);
	while (pwd[j] != '\0')
	{
		if (ft_strncmp(pwd + j, "..", 2) == 0)
			move_back_dir(new_pwd, &flag, &i, &j);
		else if (ft_strncmp(pwd + j, ".", 1) == 0)
			stay_dir(pwd, &j);
		else if (pwd[j] == '/')
			handle_slash(&flag, &j);
		else
		{
			if (flag == 1)
				new_pwd[i++] = '/';
			new_pwd[i++] = pwd[j++];
			flag = 0;
		}
	}
	return (handle_end_of_sentence(new_pwd, pwd, &i));
}

void	set_pwd_to_env_and_free(char *pwd)
{
	char	*old_pwd;
	char	*now_pwd;

	old_pwd = x_getenv("PWD");
	if (old_pwd == NULL)
		old_pwd = x_calloc(1, sizeof(char));
	set_env("OLDPWD", old_pwd);
	now_pwd = get_now_pwd(pwd, 0, 0, 1);
	set_env("PWD", now_pwd);
	free(old_pwd);
	free(g_all.now_pwd);
	g_all.now_pwd = now_pwd;
}

int	exec_cd(char **argv)
{
	char	*pwd;

	if (argv[1] == NULL)
	{
		pwd = x_getenv("HOME");
		if (pwd == NULL)
			return (cd_error("HOME not set", NULL, NULL));
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		pwd = x_getenv("OLDPWD");
		if (pwd == NULL || *pwd == '\0')
			return (cd_error("OLDPWD not set", NULL, pwd));
	}
	else
		pwd = x_strdup(argv[1]);
	if (chdir(pwd) < 0)
	{
		free(pwd);
		return (cd_error(pwd, "No such file or directory", NULL));
	}
	if (argv[1] != NULL && ft_strcmp(argv[1], "-") == 0)
		printf("%s\n", pwd);
	set_pwd_to_env_and_free(pwd);
	return (0);
}
