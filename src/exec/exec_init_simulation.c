/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:06:11 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/28 16:56:27 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// typedef struct s_minishell
// {
// 	char				*line;
// 	t_env				*env_lst;
// 	char				**env_argv;
// 	t_prs_tok_token		list; //esto hayq eu cambialo a un puntero. Volver a estudiar esto  y diferencia enntre pointer y &
// 	t_header_prs_tok	*header;
// 	struct termios		termios_default;
// }	t_minishell;


// typedef struct s_header_prs_tok
// {
// 	t_prs_tok					*header;
// 	struct s_header_prs_tok		*next;
// 	int							size;
// }	t_header_prs_tok;

// typedef struct s_prs_tok
// {
// 	char			type;
// 	char			*word;
// 	char			**cmd_flags;
// 	struct s_prs_tok *next;
// }	t_prs_tok; 


/*List of tokens - each node has 1 cmd, all redirections and etc*/
t_prs_tok	*ft_lstnew_prs_tok(char type, char *word, char **cmd_flags)
{
	t_prs_tok	*node;

	node = malloc(sizeof(t_prs_tok));
	if (!node)
		return (NULL);
	node->type = type;
	node->word = word;
	node->cmd_flags = cmd_flags;
	node->next = NULL;
	return (node);
}

/*List of headers - each pointing to a new cmd, incl, redirections, heredocs and etc*/
t_header_prs_tok	*ft_lstnew_header_prs_tok()
{
	t_header_prs_tok	*node;

	node = malloc(sizeof(t_header_prs_tok));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->size = 1;
	return (node);
}

static int	ft_lstsize_prs_tok(t_prs_tok *lst)
{
	int				i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

static t_prs_tok	*ft_lstlast_prs_tok(t_prs_tok *lst)
{
	int				i;

	i = ft_lstsize_prs_tok(lst);
	while (i > 1)
	{
		lst = lst -> next;
		i--;
	}
	return (lst);
}
void	ft_lstadd_back_prs_tok(t_prs_tok **lst, t_prs_tok *new)
{
	t_prs_tok				*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL )
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_prs_tok(*lst);
	last -> next = new;
}

void	init_simulation(t_minishell *data)
{
	t_header_prs_tok	*header_lst_node_0;
	t_header_prs_tok	*header_lst_node_1;
	t_header_prs_tok	*header_lst_node_2;
	t_prs_tok			*token_0_1;
	t_prs_tok			*token_1_1;
	t_prs_tok			*token_2_1;

	header_lst_node_0 = ft_lstnew_header_prs_tok();//create header 1
	token_0_1 = ft_lstnew_prs_tok(HEREDOC, "stop", NULL);//create token 1
	header_lst_node_0->prs_tok = token_0_1;//linking

	
	header_lst_node_1 = ft_lstnew_header_prs_tok();
	token_1_1 = ft_lstnew_prs_tok(COMMAND, NULL, ft_split("ls -a", ' '));
	header_lst_node_1->prs_tok = token_1_1;


	header_lst_node_2 = ft_lstnew_header_prs_tok();
	token_2_1 = ft_lstnew_prs_tok(COMMAND, NULL, ft_split("grep hi", ' '));
	header_lst_node_2->prs_tok = token_2_1;
	
	// ft_lstadd_back_prs_tok(&token, ft_lstnew_prs_tok(HEREDOC, "outfile", NULL));
	header_lst_node_0->next = header_lst_node_1;
	header_lst_node_1->next = header_lst_node_2;
	data->lst_prs = header_lst_node_0;
	// data->lst_prs = header_lst_node_0;
	// printf("%c %s %s %c %s\n",data->lst_prs->prs_tok->type, data->lst_prs->prs_tok->word, data->lst_prs->prs_tok->next->cmd_flags[0], data->lst_prs->prs_tok->next->next->type, data->lst_prs->prs_tok->next->next->word);
	return ;
}
