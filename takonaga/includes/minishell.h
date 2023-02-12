#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*utils*/
	/*x_func*/
void	*x_malloc(size_t size);
void	*x_calloc(size_t count, size_t size);
char	*x_strdup(char *str);
char	*x_strndup(char *str, size_t len);


#endif