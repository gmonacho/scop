NAME= scop

CC= gcc

SRC_PATH=	./srcs/
BIN_PATH= 	./bins/
INC_PATH= 	./includes/
LIBFT_PATH= ./libft/
LIBUI_PATH= ./libui/
INC_PATH=	./includes/
INCS_PATH=	./includes/\
		 	./libft/includes/\
		 	./libui/includes/


SRC= 	main.c\
		sc_create_vbo.c\
		sc_create_vao.c\
		sc_create_shader.c\
		obj_parsing.c
BIN= $(SRC:c=o)
INC= scop.h

SRCS= $(addprefix $(SRC_PATH), $(SRC))
BINS= $(addprefix $(BIN_PATH), $(BIN))
INCS= $(addprefix $(INC_PATH), $(INC))
INCI= $(addprefix -I, $(INCS_PATH))
LIBS= libft/libft.a libui/libui.a

SDLLIBS= -lSDL2 -lSDL2_ttf -lSDL2_image
OGLLIBS= -lglut -lGL -lGLU -lGLEW -DGLEW_STATIC
LDFLAGS= -L$(LIBUI_PATH) -lui -L$(LIBFT_PATH) -lft -lasan $(SDLLIBS) $(OGLLIBS)
CFLAGS+= -Wall -Wextra -Werror -g3 -fsanitize=address -fno-omit-frame-pointer 

.PHONY: all

all: $(NAME)

$(NAME): $(LIBS) $(BINS)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "->Project Compiled"

$(BIN_PATH)%.o: $(SRC_PATH)%.c
	@printf "."
	@mkdir -p $(BIN_PATH) || true
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCI)

libft/libft.a:
	@make -C $(LIBFT_PATH)

libui/libui.a:
	@make -C $(LIBUI_PATH)

.PHONY: clean

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(LIBUI_PATH)
	@rm -rf $(BIN_PATH)
	@echo "objects deleted"

.PHONY: fclean

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(LIBUI_PATH)
	@rm -r $(NAME)
	@echo "$(NAME) is deleted"

.PHONY: re

re: fclean all
