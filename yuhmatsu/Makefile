NAME := minishell
ifeq ($(shell uname), Darwin)
	CFLAGS +=  -I$(shell brew --prefix readline)/include -fsanitize=address -g -Wall -Wextra -Werror
	LDFLAGS += -L$(shell brew --prefix readline)/lib -lreadline -lhistory

else
	CFLAGS += -fsanitize=leak -g -Wall -Wextra -Werror
	LDFLAGS += -L/usr/include -lreadline
endif
INCLUDE := ./includes
LIBFT := ./libft
SRCS_DIR := ./srcs
OBJS_DIr := ./objs

SRC_FILES := execute.c expansion.c main.c tokenizer.c
SRCS := $(addprefix $(SRCS_DIR)/, $(SRC_FILES))


UTIL_FILES := x_func.c
UTILS := $(addprefix $(UTIL_DIR)/, $(UTIL_FILES))

OBJS := $(patsubst $(SRCS_DIR)%,$(OBJS_DIr)%,$(SRCS:.c=.o)) $(patsubst $(UTIL_DIR)%,$(OBJS_DIr)%,$(UTILS:.c=.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(LDFLAGS) $(LIBFT)/libft.a -o $@

$(OBJS_DIr)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIr)/$(*D)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) -rf $(OBJS_DIr)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

.PHONY: re
re: fclean all