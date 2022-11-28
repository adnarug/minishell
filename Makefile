NAME = minishell
SRC_DIR = src/
OBJ_DIR = obj/
FLAGS = -Wextra -g -Wall #-Werror 
LIBFT = libft/
CC = gcc
SRC_FILES = main				\
			utils				\
			lst_utils 			\
			lexer/lexer_main	\
			lexer/lexer_tools	\
			lexer/lexer_quote	\
			lexer/lexer_word	\
			lexer/lexer_meta	\
			expand/expand_main		\
			expand/expand_tools	\
			signals/signals_main \
			signals/signals_termios	\
			signals/signals_child_process \
			signals/signals_parent_process \
			exec/execution_main \
			exec/exec_init_simulation \
			exec/cmd_exec/path_check \
			exec/exec_redir_simulation \
			exec/exec_hdoc_simulation \
			exec/exec_hdoc_utils \
			exec/exec_rm_tools \
			exec/trans_last \
			env/env_main \
			env/initializer_env \
			utils/lst_utils \
			utils/ft_atol \
			utils/utils \
			builtins/cd \
			builtins/echo \
			builtins/env \
			builtins/exit \
			builtins/export \
			builtins/pwd \
			builtins/unset \
			# parser/parser 		\

DEF_COLOR = \033[0;80m
GREEN = \033[0;92m

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

OBJF = .cache_exists

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) libft/libft.a -lreadline $(OBJ) -o $(NAME)
	@echo "$(GREEN)minishell compiled$(DEF_COLOR)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser/
	@mkdir -p $(OBJ_DIR)/lexer/
	@mkdir -p $(OBJ_DIR)/expand/
	@mkdir -p $(OBJ_DIR)/signals/
	@mkdir -p $(OBJ_DIR)/env/
	@mkdir -p $(OBJ_DIR)/utils/
	@mkdir -p $(OBJ_DIR)/builtins/
	@mkdir -p $(OBJ_DIR)/exec/
	@mkdir -p $(OBJ_DIR)/exec/cmd_exec/
	@mkdir -p $(OBJ_DIR)/exec/pipex/

run: all
	@./minishell
	
clean:
	@rm -r $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf make $(NAME)
	@rm -rf minishell
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re