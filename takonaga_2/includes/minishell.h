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
# define TK_START 1
# define TK_PIPE 2
# define TK_ADD_OUTPUT 3
# define TK_OUTPUT 4
# define TK_DELIMITER 5
# define TK_INPUT 6

# define UNCLOSED 0
# define OPERATOR 1

# define ERROR_TOKENIZE 258
# define NUM_STR_LEN 4
# define MAX_LEN 256

# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token	t_token;
extern int 	last_status;

struct s_token
{
	char	*word;
	size_t	kind;
	t_token	*next;
};

typedef struct s_fds
{
	int		*input_fds;
	int		*output_fds;
	size_t	input_count;
	size_t	output_count;
	size_t	input_index;
	size_t	output_index;
}t_fds;

int		interpret(char *const line);

t_token	*my_tokenizer(char *line);

char	**expansion(t_token *tok, int *now_input_fd, int *now_output_fd);

void	*x_malloc(size_t size);
void	*x_calloc(size_t count, size_t size);
char	*x_strdup(char *str);
char	*x_strndup(char *str, size_t len);

bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_space(char *line, size_t i);
size_t	is_operator(char *line);
size_t	get_kinds(char *word);

char	*get_env_len(char *word, size_t *i, size_t *len);

size_t	get_len_word(char *word);

size_t	token_size(t_token *tok);
int		free_argv_token(char **argv, t_token *tok);
size_t	my_strlcat(char *dst, char *src, size_t dstsize);

void	fatal_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *l, const char *m, int s) __attribute__((noreturn));
void	err_msg(const char *location, const char *msg);

#endif
