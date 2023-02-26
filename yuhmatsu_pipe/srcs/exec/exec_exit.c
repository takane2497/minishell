/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:42:56 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/26 12:12:15 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define EXIT "exit: "

#define PROPER 0
#define OVERFLOW 1
#define NON_NUMERIC 1

unsigned int	checker(long *ans, long tmp, long sig)
{
	long	div_max;
	long	mod_max;

	div_max = LONG_MAX / 10;
	mod_max = LONG_MAX % 10;
	if (sig == 1 && (*ans > div_max || (*ans == div_max && tmp > mod_max)))
		return (OVERFLOW);
	if (sig == -1 && (*ans > div_max || (*ans == div_max && tmp > mod_max + 1)))
		return (OVERFLOW);
	return (PROPER);
}

int	minishell_atol(char *str, int *status)
{
	size_t	i;
	long	ans;
	long	sign;

	i = 0;
	ans = 0;
	sign = 1;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	i += (str[i] == '+' || str[i] == '-');
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (checker(&ans, str[i] - '0', sign))
			break ;
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (NON_NUMERIC);
	*status = (int)(ans * sign);
	return (PROPER);
}

int	exec_exit(char **argv)
{
	int	status;

	ft_dprintf(STDERR_FILENO, "exit\n");
	if (argv[1] == NULL)
		exit(g_all.last_status);
	if (minishell_atol(argv[1], &status))
	{
		ft_dprintf(STDERR_FILENO, "%s%s%s: numeric argument required\n", \
						ERROR_PREFIX, EXIT, argv[1]);
		exit(255);
	}
	if (argv[2] != NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s%stoo many arguments\n", \
					ERROR_PREFIX, EXIT);
		exit(1);
	}
	exit(status);
}
