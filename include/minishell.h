/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:44:52 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:52:41 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include <string.h>
# include <sys/param.h>
# include <errno.h>
# include "../libft/libft.h"
# include "struct.h"
# include "error.h"

// DEFINE SEPARATORS: metacharacter , they will be also used 
//to identify the type of node
# define MAIN				1
# define SPACE				' '
# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'
# define DOLLAR				'$'
# define SLASH				'/'
# define REDIRECT_IN		'<'
# define REDIRECT_OUT		'>'
# define PIPE				'|'
# define APPEND				'+'
# define HEREDOC			'-'
# define WORD				'w'
# define QUOTE_OFF			'\0'
# define COMMAND			'c'

# define CHILD_PROCESS				0
# define MAIN_PROCESS				1
# define HDOC						2
# define RIGHTS						0644
# define CMD_NOT_FOUND				127
# define CMD_NOT_FOUND				127
# define INVALID_EXIT_ARG			255
# define TERMINATED_BY_CTRL_C		130
# define PIPE_SYNTAX_ERROR			258

# define DELIMITERS		" \t|<>"
# define SPACE_STRNG		" "
# define REDIRECT		"+-<>"
# define METACHAR		"|+-<>"

int					g_glob_var_exit;

void				lex_pars_execut(t_minishell *data);
//Initialzaier
void				initializer_data(t_minishell *data);
void				initializer_data_error(t_minishell *data);
//Parser main functions
void				ft_parser(t_minishell *data);
t_sublist_prs_tok	*create_sublist(t_minishell *data, t_nod_token **current);
//Parser tokens
void				parsing_tokens(t_minishell *data, t_nod_token **current, \
					t_sublist_prs_tok *sub_list_pars);
void				creat_prsdtk_cmd(t_minishell *data, \
					t_nod_token **current, t_sublist_prs_tok *sub_list_pars);
int					count_arguments(t_nod_token *current);
int					check_number_commds(t_minishell *data);
void				creat_prsdtk_redir(t_minishell *data, \
					t_nod_token **current, t_sublist_prs_tok *sub_list_pars);
//src/parser/distribute_parser.c
t_sublist_prs_tok	*reorder_nofirst(t_sublist_prs_tok *sublist);
t_sublist_prs_tok	*reorder(t_sublist_prs_tok *sublist);
void				ft_distribute_parse(t_minishell *data);
void				send_end_node(t_sublist_prs_tok **sublist, \
					t_prs_tok **current, t_prs_tok **prev);

//src/parser/merge_parstok.c
t_sublist_prs_tok	*merge_parstk_comm(t_sublist_prs_tok *sublist);
t_sublist_prs_tok	*new_parsdtk_cmd(t_sublist_prs_tok *sublist, \
					t_prs_tok **current, char **new_array_cmd);
char				**count_commands(t_prs_tok *current);
t_sublist_prs_tok	*del_cmd_parsdlist(t_sublist_prs_tok *sublist, \
					t_prs_tok **runner);
char				**create_array_cmd(t_prs_tok *runner, int nb);
t_sublist_prs_tok	*del_list_allprstk_sorted(t_sublist_prs_tok *sublist);

//Parser tools
t_prs_tok			*find_last_parsedtok(t_sublist_prs_tok *sub_list_pars);
void				add_parsedtok_sublist(t_prs_tok *parsedtok_redir, \
					t_sublist_prs_tok *sub_list_pars);
void				data_input(t_minishell *data);
void				print_list_parsedtoken(t_minishell *data);
void				print_list_parsedtoken2(t_sublist_prs_tok *sub_list_pars);
void				print_parsedtok(t_prs_tok *current_parsedtoken);
void				del_parsedtk_and_list_tok(t_minishell *data);
void				free_parsed_tok(t_prs_tok	*delete);
void				free_list_parsedtok(t_sublist_prs_tok *sublist);
void				add_toke_list(t_list_token *list, t_nod_token *new);
t_nod_token			*create_tok(t_lexing *lex_struct);
t_nod_token			*find_last_node(t_list_token *list);
void				delete_list(t_list_token *list);
void				initializer_lex(t_lexing *lex_struct);
void				ft_lexer(t_minishell *data);
void				lexer_meta(t_minishell *data, t_lexing *lex_struct);
void				lexer_word(t_minishell *data, t_lexing *lex_struct);
void				lex_redirect(t_minishell *data, t_lexing *lex_struct);
int					are_quote_closed(t_minishell *data);
int					change_quot_modus(char *quote, char c);
int					ft_isspace(char c);
int					ft_ismeta(char c);
int					ft_isspecialchar(char c);
int					ft_isredirect(char c);
//List tools
void				print_list(t_list_token *list);
void				print_token(t_nod_token	*token);
void				free_all_exec(t_minishell *data);
void				add_or_replace(t_env *node_to_add, \
					char *key, char *val, t_env *list);
//Misc list functions
int					builtin_pwd(char *args_cd);
t_env				*ft_node_init(char *envp);
void				ft_lstadd_back_mini(t_env **lst, t_env *new);
char				*ft_copy_key(char *string);
void				print_2d(char **array);
int					count_strings(char **array);
void				print_env_lst(t_env *env_lst);
void				ft_lst_free(t_env *lst);
void				ft_free_2d(char **table);
t_env				*ft_lstlast_mini(t_env *lst);
void				ft_lstadd_back_mini(t_env **lst, t_env *new);
t_env				*ft_lstnew_env(char *value, char *key);
int					counter_2d(char **cmd_flags);
void				del_array_list_prsdtok(t_minishell *data);
void				make_envp(char *s, t_minishell *data);
//Expansion
void				ft_expand(t_minishell *data);
void				expand_find(t_minishell *data, t_nod_token *current);
char				*expand_variable(t_minishell *data, char **s);
char				*perform_expansion(t_minishell *data, \
					char *old_buf, char **s_arr);
//Signals
void				signals_main(struct termios *per_default);
void				sigint_main(void);
void				sigquit_main(void);
void				new_prompt(int signal);
void				no_print_ctrlc(struct termios *per_default);
void				reset_print_ctrlc(struct termios *per_default);
void				signals_heredoc_process(void);
void				signals_child_process(struct termios *per_default);
void				sigint_child(void);
void				sigquit_child(void);
void				signals_parent_process(void);
void				sigint_parent(void);
void				sigquit_parent(void);
//Tool and utils functions
int					is_not_end_expand(char c);
void				check_leaks(void);
int					builtin_echo(t_minishell *data);
int					builtin_pwd(char *args_cd);
char				**dup_env_matrix(char **matrix);
t_env				*ft_node_init(char *envp);
t_env				*create_env_lst(char **dup_env);
void				ft_lstadd_back_mini(t_env **lst, t_env *new);
char				*ft_copy_key(char *string);
void				print_2d(char **array);
int					count_strings(char **array);
void				print_env_lst(t_env *env_lst);
void				ft_lst_free(t_env *lst);
void				ft_free_2d(char **table);
t_env				*ft_lstlast_mini(t_env *lst);
void				ft_lstadd_back_mini(t_env **lst, t_env *new);
t_env				*ft_lstnew_env(char *key, char *value);
t_env				*ft_lstdelone_env(t_env *node_to_delete, t_env *env);
t_env				*ft_lst_find(t_env *node, char *key);
t_env				*ft_lst_find_previous(t_env *head, t_env *node_to_find);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_execution(t_minishell *data);
void				count_size(t_minishell *data);
int					at_least_one_cmd(t_minishell *data, \
					t_sublist_prs_tok *list);
void				ft_env(t_minishell *data, char **envp);
void				print_env_lst_export(t_env *env_lst);
void				free_loop_exec(t_minishell *data);
//Refactored libft
long long			ft_atol(const char *str, bool *error);
//Builtins
int					builtin_env(t_env *env, char *argv);
int					builtin_cd(t_env *env, char **argv);
int					builtin_unset(t_minishell *data, t_env *env, char **argv);
int					builtin_export(t_minishell *data);
int					builtin_exit(t_minishell *data);
int					is_builtin(t_prs_tok *token);
char				*create_key(char *s, int *i, t_minishell *data);
void				real_env(t_minishell *data);
bool				first_char(char c);
bool				valid_check(char *line);
//Execution 
int					exec_builtin(t_minishell *data);
char				**find_path(char **envp);
char				*check_paths(char **path_to_builtins, char	*command);
int					find_correct_paths(t_prs_tok *parameters, \
					t_minishell *data);
void				check_for_reset(t_minishell *data, int i);
///HDOCS
int					count_hdocs(t_minishell *data);
void				destroy_hdocs(t_minishell *data);
void				init_hdocs(t_minishell *data);
void				reassign_hdoc_to_redir(t_minishell *data);
t_prs_tok			*find_hdoc_nodes(t_minishell *data);
//Execution, redirections, pipes
void				exec_cmd(t_minishell *data, t_prs_tok *token);
void				pipe_last_cmd(t_minishell *data);
void				pipe_transitory_cmd(t_minishell *data);			
void				redirect_stdin_to_pipe(t_minishell *data);
void				redirect_transitory_cmd(t_minishell *data);
int					create_fork(t_minishell *data);
void				exec_bash_cmd(t_minishell *data);
void				init_exec(t_minishell *data);
void				reset_stdin_stdout(t_minishell *data);
void				reset_params(t_minishell *data);
void				dup_stdin_and_stdout(t_minishell *data);
void				reset_stdin_stdout(t_minishell *data);
int					create_pipe(t_minishell *data);
void				catch_exit_code(t_minishell *data);
void				close_fds_in_out(t_minishell *data);
void				exec_transitory_builtin(t_minishell *data);
void				exec_last_builtin(t_minishell *data);
void				redirect_last_cmd(t_minishell *data);
int					resolve_redir(t_sublist_prs_tok *prs_lst, \
					t_minishell *data);
int					resolve_hdocs(t_minishell	*data);
void				wait_signal(t_minishell *data, int status);
void				run_dup2(int fd_old, int fd_new);
t_env				*unseting_first_node(t_env *node_to_delete, t_env *env);
//Error
void				print_error_free_exit(t_minishell *data, char *error_msg, \
					int glb_var, bool do_exit);
void				exec_exit(t_minishell *data, char *error_msg, \
					int glb_var, bool do_exit);
void				my_strerror(char *err_cmd, int err_num);
void				cmd_str_error(char *err_cmd, char *err_msg);
void				free_all(t_minishell *data);
void				print_error_free_exit(t_minishell *data, \
					char *error_msg, int glb_var, bool do_exit);
void				strerr_export(char *err_cmd, int err_num, char *s);
void				strerr_unset(char *err_cmd, char *s);
void				cmd_str_access(char *s);

#endif 