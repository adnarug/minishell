/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:06:11 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/25 19:57:21 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// typedef struct s_minishell
// {
// 	char				*line;
// 	t_env				*env_lst;
// 	char				**env_argv;
// 	t_prs_tok_token		list; //esto hayq eu cambialo a un puntero. Volver a estudiar esto  y diferencia enntre pointer y &
// 	t_sublist_prs_tok	*header;
// 	struct termios		termios_default;
// }	t_minishell;


// typedef struct s_sublist_prs_tok
// {
// 	t_prs_tok					*header;
// 	struct s_sublist_prs_tok		*next;
// 	int							size;
// }	t_sublist_prs_tok;

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
t_sublist_prs_tok	*ft_lstnew_header_prs_tok()
{
	t_sublist_prs_tok	*node;

	node = malloc(sizeof(t_sublist_prs_tok));
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
	t_sublist_prs_tok	*header_lst;
	t_prs_tok			*token;
	

	token = ft_lstnew_prs_tok('<', "infile", NULL);
	header_lst = ft_lstnew_header_prs_tok();
	ft_lstadd_back_prs_tok(&token, ft_lstnew_prs_tok('c', NULL, ft_split("pwd", ' ')));
	ft_lstadd_back_prs_tok(&token, ft_lstnew_prs_tok('>', "outfile", NULL));
	header_lst->prs_tok = token;
	data->lst_prs = header_lst;
	printf("%c %s %s %c %s\n",data->lst_prs->prs_tok->type, data->lst_prs->prs_tok->word, data->lst_prs->prs_tok->next->cmd_flags[0], data->lst_prs->prs_tok->next->next->type, data->lst_prs->prs_tok->next->next->word);
	return ;
}