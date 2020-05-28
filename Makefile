EXEC = scop

CC = gcc

SRCS = srcs/main.c

HEADERS = -Ilibft/includes/\
		 -Iincludes/\

OBJS = $(SRCS:.c=.o)

LDFLAGS= -Llibft/ -lft -lasan

CFLAGS += -Wall -Wextra -Werror -g -fsanitize=address

all: $(EXEC) clean

$(EXEC): $(OBJS)
	make -C libft
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(HEADERS)

clean:
	@rm -rf $(OBJS)
	@echo "objects deleted"

fclean: clean
	rm -rf $(EXEC)
	@echo "$(EXEC) is deleted"

re: fclean all

.PHONY: clean
		fclean
		re
