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

# define UNCLOSED 0
# define OPERATOR 1

# define ERROR_TOKENIZE 258
# define NUM_STR_LEN 4
# define MAX_LEN 256

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token	t_token;
extern int	last_status;
extern char numstr[NUM_STR_LEN];

typedef struct s_token
{
	char	*word;
	size_t	kind;
	t_token	*next;
}t_token;

int		interpret(char *const line);

t_token	*my_tokenizer(char *line);

char	**expansion(t_token *tok);

void	*x_malloc(size_t size);
void	*x_calloc(size_t count, size_t size);
char	*x_strdup(char *str);
char	*x_strndup(char *str, size_t len);
char	*for_free(char *res, char *free_str);

bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_space(char *line, size_t i);
size_t	is_operator(char *line);

char	*get_env_len(char *word, size_t *i, size_t *len);

size_t	get_len_word(char *word);

size_t	token_size(t_token *tok);
void	free_argv_token(char **argv, t_token *tok);
size_t	my_strlcat(char *dst, char *src, size_t dstsize);

void	fatal_error(const char *msg);
void	err_exit(const char *location, const char *msg, int status);

#endif
