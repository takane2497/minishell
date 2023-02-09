CFLAGS = -Wall -Wextra -Werror
SRCS = test_prompt.c
NAME = minishell
INCLUDE = -I$(shell brew --prefix readline)/include
LIBS = -L$(shell brew --prefix readline)/lib -lreadline
RLDIR=`brew --prefix readline`
CC = gcc

.c.o:
	$(CC) -c $(CFLAGS) $^ -o $@

all : $(NAME)
	
$(NAME) : $(SRCS:.c=.o)
	$(CC) -o $(NAME) $(SRCS:.c=.o) $(INCLUDE) $(LIBS)

clean :
	rm -f $(SRCS:.c=.o) $(BONUS:.c=.o)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean re fclean