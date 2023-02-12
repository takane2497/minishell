/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:25:15 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/02/11 17:25:16 by yuhmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TK_WORD 0
# define TK_OP 1
# define TK_EOF 2
# define TK_START 3

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token	t_token;

typedef struct s_token
{
	char	*word;
	size_t	kind;
	t_token	*next;
}t_token;

t_token	*my_tokenizer(char *line);
char	**expansion(t_token *tok);
int		interpret(char *const line);

void	*x_malloc(size_t size);
void	*x_calloc(size_t count, size_t size);
char	*x_strdup(char *str);
char	*x_strndup(char *str, size_t len);

#endif
