/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takonaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:06:48 by takonaga          #+#    #+#             */
/*   Updated: 2023/02/23 07:06:49 by takonaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_argv_token(char **argv, t_token *tok)
{
	size_t	i;
	t_token	*tmp;

	while (tok != NULL)
	{
		free(tok->word);
		tmp = tok->next;
		free(tok);
		tok = tmp;
	}
	i = 0;
	if (argv == NULL)
		return (0);
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return (0);
}

void	free_tok(t_token *tok)
{
	t_token	*tmp;

	while (tok != NULL)
	{
		free(tok->word);
		tmp = tok->next;
		free(tok);
		tok = tmp;
	}
}

void	free_argv(char **argv)
{
	size_t	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
