NAME := minishell
ifeq ($(shell uname), Darwin)
	CFLAGS +=  -I$(shell brew --prefix readline)/include -g -Wall -Wextra -Werror
	LDFLAGS += -L$(shell brew --prefix readline)/lib -lreadline #-lhistory

else
	CFLAGS += -fsanitize=leak -g -Wall -Wextra -Werror
	LDFLAGS += -L/usr/include -lreadline
endif
INCLUDE := ./includes
LIBFT := ./libft
SRCS_DIR := ./srcs
OBJS_DIR := ./objs
UTIL_DIR := utils


UTIL_FILES := x_func.c validate_char.c utils_for_expansion.c error_handling.c
UTILS := $(addprefix $(UTIL_DIR)/, $(UTIL_FILES))

SRC_FILES := execute.c expansion.c main.c tokenizer.c get_env_len.c get_len_word.c redirect.c exec_builtin.c exec_export.c exec_pwd.c $(UTILS)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRC_FILES))

OBJS := $(patsubst $(SRCS_DIR)%,$(OBJS_DIR)%,$(SRCS:.c=.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(LDFLAGS) $(LIBFT)/libft.a -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)/$(*D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) -rf $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

.PHONY: re
re: fclean all