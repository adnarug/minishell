NAME = minishell.a
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
			exec/redirs_hdocs/exec_redir_simulation \
			exec/redirs_hdocs/exec_hdoc_simulation \
			exec/redirs_hdocs/exec_hdoc_utils \
			exec/cmd_exec/pipe_operations \
			exec/cmd_exec/exec_tools \
			exec/cmd_exec/exec_utils \
			exec/cmd_exec/execution_redir \
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
	@ar rcs $(NAME) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a minishell.a -lreadline -o minishell
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
	@mkdir -p $(OBJ_DIR)/exec/redirs_hdocs/
	@mkdir -p $(OBJ_DIR)/exec//

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