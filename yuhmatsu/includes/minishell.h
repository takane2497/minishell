/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhmatsu <yuhmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:25:15 by yuhmatsu          #+#    #+#             */
/*   Updated: 2023/03/06 22:48:12 by yuhmatsu         ###   ########.fr       */
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

# define INTERRUPTED 0
# define CONTINUE 1

# define ERROR_PREFIX "minishell: "

# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token	t_token;
typedef struct s_all	t_all;
typedef struct s_env	t_env;
typedef struct s_fds	t_fds;
extern t_all			g_all;

struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
};

struct s_all
{
	int		last_status;
	char	**environ;
	char	*now_pwd;
	t_env	*envs;
	size_t	heredoc_status;
	pid_t	last_pid;
};

struct s_token
{
	char	*word;
	size_t	kind;
	t_token	*next;
};

struct s_fds
{
	int		now_input_fd;
	int		now_output_fd;
	int		old_pipe_input_fd;
	size_t	num_pipe;
	size_t	i;
};

ssize_t	ft_strchr_pointer(const char *s, char c);

int		interpret(char *const line);
pid_t	exec(char *argv[], size_t *i, t_fds *fds);
char	*search_path(const char *filename);
void	validate_access(const char *path, const char *filename);

size_t	count_pipe(t_token *tok);
int		all_wait(size_t	i);

int		read_heredoc(const char *delimiter);

t_token	*my_tokenizer(char *line, t_token *tok_head);
t_token	*new_token(char *word);

size_t	concat_char(char *str, char *word, size_t *i);
char	**expansion(t_token **tok, int *now_input_fd, int *now_output_fd);

void	*x_malloc(size_t size);
void	*x_calloc(size_t count, size_t size);
char	*x_strdup(char *str);
char	*x_strndup(char *str, size_t len);
char	*x_getenv(char *env_name);

bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_space(char *line, size_t i);
size_t	is_operator(char *line);
size_t	get_kinds(char *word);

char	*get_env_len(char *word, size_t *i, size_t *len);
size_t	get_len_word(char *word);

size_t	token_size(t_token *tok, size_t *size);
int		free_argv_token(char **argv, t_token *tok);
size_t	my_strlcat(char *dst, char *src, size_t dstsize);
size_t	init_expansion(char ***argv, t_token **tmp, size_t *i, t_token *tok);

void	fatal_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *l, const char *m, int s) __attribute__((noreturn));
void	err_msg(const char *location, const char *msg);

t_token	*prepare_to_redirect_input(t_token *tmp, int *now_input_fd);
t_token	*prepare_to_redirect_output(t_token *tmp, int *now_output_fd);
void	redirect(int *now_input_fd, int *now_output_fd);
void	undo_redirect(int now_input_fd, int now_output_fd);

char	*remove_quote(char *word);

size_t	is_builtin(char *command);
int		exec_in_builtin(char **argv, int now_input_fd, int now_output_fd);

int		exec_pwd(char **argv);
int		exec_export(char **argv);
int		exec_echo(char **argv);
int		exec_unset(char **argv);
int		exec_env(void);
int		exec_cd(char **argv);
int		exec_exit(char **argv);

void	init_current_dir1(char *new_pwd, size_t *i, size_t *j);
void	init_current_dir2(char *new_pwd, char *pwd, size_t *i, size_t *j);
void	move_back_dir(char *new_pwd, size_t *flag, size_t *i, size_t *j);
void	stay_dir(char *pwd, size_t *j);
void	handle_slash(size_t	*flag, size_t *j);

size_t	set_env(char *env_str, char *new_value);

void	free_argv(char **argv);
void	free_tok(t_token *tok);

void	init_signal(void);
void	signal_in_signal(void);
void	signal_in_heredoc(void);
#endif
