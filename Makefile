EXEC = scop

CC = gcc

SRCS = srcs/main.c

HEADERS =	-I./includes/\
			-I./libft/includes/\
			-I./libui/includes

OBJS = $(SRCS:.c=.o)

LDFLAGS= -L./libui -lui -L./libft -lft -lasan -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image

CFLAGS += -Wall -Wextra -Werror -g -fsanitize=address

all: $(EXEC)

$(EXEC): $(OBJS)
		@make -C libft
		@make -C libui
		@$(CC) -o $@ $^ $(LDFLAGS)
		@mkdir ./bin 2> /dev/null || true
		@mv $(OBJS) ./bin
		@echo "Project Compiled"

%.o: %.c
		@$(CC) -o $@ -c $< $(CFLAGS) $(HEADERS)

clean:
	@make clean -C libft
	@make clean -C libui
	@rm -rf ./bin/$(OBJS)
	@echo "objects deleted"

fclean: clean
	@make fclean -C libft
	@make fclean -C libui
	@rm -rf $(EXEC)
	@echo "$(EXEC) is deleted"

re: fclean all

.PHONY: clean
		fclean
		re
