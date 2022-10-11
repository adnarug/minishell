NAME = minishell.a
SRC_DIR = src/
OBJ_DIR = obj/
FLAGS = -Werror -Wextra -Wall
PRINTF = Printf/
CC = gcc
SRC_FILES = main
AR	=	ar rcs
DEF_COLOR = \033[0;80m
GREEN = \033[0;92m

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

OBJF = .cache_exists

$(NAME): $(OBJ)
	@make -C Printf/
	@$(AR) $(NAME) $(OBJ) 
	@$(CC) $(NAME) $(FLAGS) Printf/libftprintf.a minishell.a -o minishell
	@echo "$(GREEN)minishell compiled$(DEF_COLOR)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -r $(OBJ_DIR)
	@rm -rf a.out
	@make clean -C $(PRINTF)

fclean: clean
	@rm -f $(NAME)
	@rm -rf minishell
	@rm -rf minishell.a
	@make fclean -C $(PRINTF)

re: fclean all

.PHONY: all, clean, fclean, re