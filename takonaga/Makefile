NAME := minishell
ifeq ($(shell uname), Darwin)
	CFLAGS +=  -I$(shell brew --prefix readline)/include -fsanitize=address -g -Wall -Wextra -Werror
	LDFLAGS += -L$(shell brew --prefix readline)/lib -lreadline

else
	CFLAGS += -fsanitize=leak -g -Wall -Wextra -Werror
	LDFLAGS += -L/usr/include -lreadline
endif
INCLUDE := ./include
LIBFT := ./libft
SRCS_DIR := ./src
OBJS_DIr := ./objs

SRCS := $(SRCS_DIR)/main.c \

OBJS := $(patsubst $(SRCS_DIR)%,$(OBJS_DIr)%,$(SRCS:.c=.o))

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