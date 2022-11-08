NAME = minishell.a
SRC_DIR = src/
OBJ_DIR = obj/
FLAGS = -Werror -Wextra -g -Wall
LIBFT = libft/
CC = gcc
SRC_FILES = main				\
			builtins			\
			utils				\
			lst_utils 			\
			lexer/lexer_main	\
			lexer/lexer_tools	\
			lexer/lexer_quote	\
			lexer/lexer_word	\
			lexer/lexer_meta	\
			expand/expand		\
			expand/expand_tools	\
			env/env_main \
			env/initializer_env \
			utils/lst_utils \
			utils/ft_atol \
			utils/utils \
			# parser/parser 		\


AR	=	ar rcs
DEF_COLOR = \033[0;80m
GREEN = \033[0;92m

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

OBJF = .cache_exists

$(NAME): $(OBJ)
	@make -C libft/
	@$(AR) $(NAME) $(OBJ) 
	@$(CC) $(NAME) $(FLAGS) libft/libft.a minishell.a -lreadline -o minishell
	@echo "$(GREEN)minishell compiled$(DEF_COLOR)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser/
	@mkdir -p $(OBJ_DIR)/lexer/
	@mkdir -p $(OBJ_DIR)/expand/
	@mkdir -p $(OBJ_DIR)/env/
	@mkdir -p $(OBJ_DIR)/utils/


clean:
	@rm -r $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf make $(NAME)
	@rm -rf minishell
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re