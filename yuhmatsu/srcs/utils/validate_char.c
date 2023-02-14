/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:05:40 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/12 22:05:41 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

bool	is_space(char *line, size_t i)
{
	return (line[i] == ' ' || line[i] == '\t' || line[i] == '\n');
}

size_t	is_operator(char *line)
{
	if (ft_strncmp(line, "||", 2) == 0)
		return (3);
	if (ft_strncmp(line, "|", 1) == 0)
		return (1);
	if (ft_strncmp(line, ">>>", 3) == 0)
		return (3);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	if (ft_strncmp(line, "<<<", 3) == 0)
		return (3);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(line, "<", 1) == 0)
		return (1);
	return (0);
}

size_t	get_kinds(char *word)
{
	if (ft_strncmp(word, "|", 1) == 0)
		return (TK_PIPE);
	if (ft_strncmp(word, ">>", 2) == 0)
		return (TK_ADD_OUTPUT);
	if (ft_strncmp(word, ">", 1) == 0)
		return (TK_OUTPUT);
	if (ft_strncmp(word, "<<", 2) == 0)
		return (TK_DLIMITER);
	if (ft_strncmp(word, "<", 1) == 0)
		return (TK_INPUT);
	return (TK_WORD);
}